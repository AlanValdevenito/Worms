#include "game.h"
#include <chrono>
#include <thread>

#define TURN_DURATION 60

Game::Game(Queue<std::shared_ptr<Dto>> &queue, Broadcaster &broadcaster) : common_queue(queue),
                                                                           broadcaster(broadcaster),
                                                                           world(World()),
                                                                           game_finished(false)
{

    /* VIGAS */

    world.addBeam(3, 9, 0, LONG);  // Ocupa del 1 al 6
    world.addBeam(9, 9, 0, LONG);  // Ocupa del 7 al 12
    world.addBeam(15, 9, 0, LONG); // Ocupa del 13 al 18
    world.addBeam(21, 9, 0, LONG); // Ocupa del 19 al 24
    world.addBeam(27, 9, 0, LONG);
    world.addBeam(33, 9, 0, LONG);
    world.addBeam(39, 9, 0, LONG);
    world.addBeam(45, 9, 0, LONG);
    world.addBeam(51, 9, 0, LONG);

    world.addBeam(3, 16, 0, LONG); // Ocupa del 1 al 6

    /* WORMS */

    world.addWorm(2, 12);
    world.addWorm(4, 12);
    
    createPlayers();
}

void Game::createPlayers() {
    int numberOfWorms = (int)world.getWorms().size();
    int wormId = 1;
    int playerId = 1;
    for (int i = 0; i < numberOfPlayers; i++) {
        std::vector<int> wormIds;
        for (int j = 0; j < numberOfWorms / numberOfPlayers; j++) {
            wormIds.push_back(wormId);
            world.getWormsById()[wormId]->setPlayerId(playerId);
            wormId++;
        }
        players.push_back(Player(playerId, wormIds));
        playerId++;
    }
}

void Game::run()
{   
    begin = std::chrono::steady_clock::now();
    while (not game_finished)
    {
        std::shared_ptr<Dto> dto;
        if (common_queue.try_pop(dto))
        {   

            if (dto->is_alive() && dto->return_code() == FINALIZAR_CODE) {
                broadcaster.removeQueueWithId(dto->get_cliente_id()); // elimino la queue del cliente que murio
                broadcaster.notificarCierre(dto);
                broadcaster.deleteAllQueues(); // aviso a los demas que cierren
                stop();
                break;
            }
            // if (not dto->is_alive()) {
            //     stop();
            //     broadcaster.deleteAllQueues();
            // }
            executeCommand(dto);
        }
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    
        // broadcast();
    }
}

void Game::passTurn() {
    // cambio de turno 
    end = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() >= TURN_DURATION) {
        std::cout << "pasaron " << TURN_DURATION << " segundos, cambio de turno\n";
        std::cout << "turno actual = " << idTurn << "\n";
        begin = std::chrono::steady_clock::now();
        if (idTurn == 1) {
            idTurn = 2;
        } else  if (idTurn == 2) {
            idTurn = 1;
        }
        players[idTurn - 1].changeActualWorm();
    }
}

void Game::update()
{
    world.step();
    passTurn();
    
    // actualizo los gusanos
    for (Worm *worm : world.getWorms()) {
        if (not worm->isMoving() && worm->getHp() == 0) {
            worm->is_alive = false;
            // saco el gusano del juego
            
            players[worm->playerId - 1].numberOfAliveWorms--;
            /*int idWorm = worm->getId();
            world.getWorms().remove(worm);
            world.getWormsById().erase(idWorm);
            int indexOfWormToRemove = 0;
            // busco el indice del gusano dentro del vector de ids de gusanos del player
            for (int i = 0; i < (int)players[worm->playerId - 1].size(); i++) {
                if (players[worm->playerId - 1].wormIds[i] == idWorm) {
                    indexOfWormToRemove = i;
                    break;
                }
            }
            players[worm->playerId - 1].wormIds.erase(indexOfWormToRemove);
            */
        }
        worm->makeDamage();
    }

    // actualizo los players
    for (int i = 0; i < numberOfPlayers; i++) {
        if (players[i].numberOfAliveWorms == 0) {
            broadcaster.notificarCierre(std::make_shared<Dto>(FINALIZAR_CODE,1));
            broadcaster.deleteAllQueues(); // aviso a los demas que cierren
            stop();
            return;
        }
    }
    sendWorms();
}

void Game::sendWorms()
{   

    std::vector<std::shared_ptr<Gusano>> vectorGusanos;
    for (Worm *w : world.getWorms())
    {   
        if (w->isAlive() || w->isMoving()) {
            if ((int)w->getHp() < 100) {
                //std::cout << "hp = " << (int)w->getHp() << "\n";
            }
            std::shared_ptr<Gusano> g = std::make_shared<Gusano>((w->getId()),
                                                        (int)(w->getXCoordinate() * 100),
                                                        (int)(w->getYCoordinate() * 100),
                                                        w->getHp());
            vectorGusanos.push_back(g);
        }

        // IF NO ESTA VIVO Y ESTA QUIETO O COLISIONANDO CONTRA LA VIGA -> LO ELIMINAS

    }
    std::shared_ptr<Gusanos> gusanos = std::make_shared<Gusanos>(vectorGusanos);

    int id = players[idTurn - 1].getActualWormId(); // obtengo el id del gusano actual
    gusanos->set_gusano_de_turno(id);

    broadcaster.AddGusanosToQueues(gusanos);
}


void Game::sendMap()
{
    std::vector<std::shared_ptr<Viga>> vs;
    // por cada viga manda un Dto Viga a los senders
    for (auto &beam : world.getBeams())
    {
        // cambiar los parametros a float
        std::shared_ptr<Viga> viga = std::make_shared<Viga>((int)(beam.getXCoordinate() * 100),
                                                            (int)(beam.getYCoordinate() * 100),
                                                            (int)(beam.getWidth() * 100),
                                                            (int)(beam.getHeight() * 100),
                                                            (int)(beam.getAngle()));
        
        vs.push_back(viga);
    }
    std::shared_ptr<Vigas> vigas = std::make_shared<Vigas>(vs);
    broadcaster.AddVigasToQueues(vigas);
}


void Game::moveWormRight(uint8_t id)
{

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    // lista de gusano = diccionario [ID];

    int idActualWorm = players[idTurn - 1].getActualWormId();
    world.getWormsById()[idActualWorm]->moveRight();
    // std::cout << "posicion gusano = " << world.getWorms().front()->getXCoordinate() << "\n";
}

void Game::moveWormLeft(uint8_t id)
{

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    int idActualWorm = players[idTurn - 1].getActualWormId();
    world.getWormsById()[idActualWorm]->moveLeft();
}

void Game::batWorm(uint8_t id) {
    int idActualWorm = players[idTurn - 1].getActualWormId();
    world.getWormsById()[idActualWorm]->bat(world.getWorms());
    begin = std::chrono::steady_clock::now();
    if (idTurn == 1) {
        idTurn = 2;
    } else  if (idTurn == 2) {
        idTurn = 1;
    }
    players[idTurn - 1].changeActualWorm();
}

void Game::stop()
{
    game_finished = true;
}

void Game::executeCommand(std::shared_ptr<Dto> dto)
{
    uint8_t clientId = dto->get_cliente_id();
    if (clientId != idTurn) return;
    uint8_t code = dto->return_code();
    if (code == MOVER_A_DERECHA_CODE)
    {
        moveWormRight(clientId); // SI ES SU TURNO, LE PASAMOS EL ID
    }
    else if (code == MOVER_A_IZQUERDA_CODE)
    {
        moveWormLeft(clientId); // SI ES SU TURNO, LE PASAMOS EL ID
    }
    else if (code == BATEAR_CODE) {
        batWorm(clientId);
        /*for (Worm *worm : world.getWorms()) {

            uint16_t x = worm->getXCoordinate() * 100;
            uint16_t y = worm->getYCoordinate() * 100;
            uint8_t id = worm->getId();
            uint8_t hp = worm->getHp();
            std::cout << "gusano id " << (int)id << " vida = " << (int)hp << "\n";
            std::shared_ptr<Gusano> g = std::make_shared<Gusano>(id, x, y, hp);
            broadcaster.AddGusanoToQueues(g);
        
        }*/
    }

    /*int idActualWorm = players[idTurn - 1].getActualWormId();
    for (Worm *worm : world.getWorms()) {
        if (worm->getId() == idActualWorm) {
            uint16_t x = worm->getXCoordinate() * 100;
            uint16_t y = worm->getYCoordinate() * 100;
            uint8_t id = worm->getId();
            uint8_t hp = worm->getHp();
            std::shared_ptr<Gusano> g = std::make_shared<Gusano>(id, x, y, hp);
            broadcaster.AddGusanoToQueues(g);
        }
    }*/
    // delete dto;
}

bool Game::anyWormMoving() {
    for (Worm *worm : world.getWorms()) {
        if (worm->isMoving()) {
            return true;
        }
    }
    return false;
}

Game::~Game() {}

void Game::broadcast()
{
}
