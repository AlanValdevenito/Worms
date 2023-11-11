#include "game.h"
#include <chrono>
#include <thread>

#define TURN_DURATION 60
#define TIME_LEFT_AFTER_ATTACK 5

Game::Game(Queue<std::shared_ptr<Dto>> &queue, Broadcaster &broadcaster) : common_queue(queue),
                                                                           broadcaster(broadcaster),
                                                                           world(World()),
                                                                           game_finished(false)
{
    // mapa_rampa();
    mapa_jaula();
    // mapa_puente();
}

void Game::mapa_rampa() {
    world.addBeam(26, 7.5, 90, SHORT);
    world.addBeam(26, 12, 90, LONG); 
    world.addBeam(26, 18, 90, LONG);

    world.addBeam(0.5, 12, 90, LONG);
    world.addBeam(2.5, 7, 130, LONG);
    world.addBeam(5, 5, 0, SHORT);
    world.addBeam(7.5, 5.5, 30, SHORT);
    world.addBeam(11.5, 6.2, 0, LONG);
    world.addBeam(16, 6.2, 0, LONG);
    world.addBeam(19.5, 6.7, 30, SHORT);
    world.addBeam(23.5, 7.4, 0, LONG);
    
    world.addBeam(10, 9, 0, LONG);
    world.addBeam(5.5, 9.75, 150, SHORT);

    world.addWorm(10, 14);
    world.addWorm(12, 14);
}

void Game::mapa_jaula() {
    // Piso
    world.addBeam(5, 5, 0, LONG);
    world.addBeam(11, 5, 0, LONG);
    world.addBeam(17, 5, 0, LONG);
    world.addBeam(23, 5, 0, LONG);

    // Techo
    world.addBeam(5, 17, 0, LONG);
    world.addBeam(11, 17, 0, LONG);
    world.addBeam(17, 17, 0, LONG);
    world.addBeam(23, 17, 0, LONG);

    // Paredes
    world.addBeam(2.5f, 8, 90, LONG);
    world.addBeam(2.5f, 14, 90, LONG);
    world.addBeam(25.5f, 8, 90, LONG);
    world.addBeam(25.5f, 14, 90, LONG);

    world.addWorm(4, 10);
    world.addWorm(8, 10);
}

void Game::mapa_puente() {
    world.addBeam(0, 12, 90, LONG);

    world.addBeam(3, 9, 0, LONG);
    world.addBeam(9, 9, 0, LONG);
    world.addBeam(15, 9, 0, LONG);
    world.addBeam(21, 9, 0, LONG);
    world.addBeam(27, 9, 0, LONG);
    world.addBeam(33, 9, 0, LONG);

    world.addBeam(36, 12, 90, LONG);

    world.addWorm(15, 14);
    world.addWorm(5, 14);
}

void Game::createPlayers() {
    int numberOfWorms = (int)world.getWorms().size();
    int wormId = 1;
    int teamNumber = 0;
    numberOfPlayers = (int)idPlayers.size();
    idTurn = idPlayers[indexOfActualPlayer];

    for (int playerId : idPlayers) {
        std::vector<int> wormIds;
        for (int i = 0; i < numberOfWorms / numberOfPlayers; i++) {
            wormIds.push_back(wormId);
            world.getWormsById()[wormId]->setPlayerId(playerId);
            world.getWormsById()[wormId]->setTeamNumber(teamNumber);
            wormId++;
        }
        players.push_back(Player(playerId, teamNumber, wormIds));
        teamNumber++;
    }

    actualWormId = players[indexOfActualPlayer].actualWormId;
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

void Game::addPlayerId(uint8_t id) {
    idPlayers.push_back(id);
}

void Game::passTurn() {
    // cambio de turno 
    end = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() >= TURN_DURATION ||
        (wormAttacked && std::chrono::duration_cast<std::chrono::seconds> (end - timeOfAttack).count() >= TIME_LEFT_AFTER_ATTACK)) {
        wormAttacked = false;
        std::cout << "pasaron " << TURN_DURATION << " segundos, cambio de turno\n";
        std::cout << "turno actual = " << idTurn << "\n";
        begin = std::chrono::steady_clock::now();
        if (indexOfActualPlayer == (int)idPlayers.size() - 1) {
            indexOfActualPlayer = 0;
        } else {
            indexOfActualPlayer++;
        }
        idTurn = idPlayers[indexOfActualPlayer];
        players[indexOfActualPlayer].changeActualWorm();
        actualWormId = players[indexOfActualPlayer].actualWormId;
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


    if (greenGrenade != NULL) {

        std::chrono::steady_clock::time_point now;
        now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds> (now - greenGrenade->spawnTime).count() >= greenGrenade->timeToExplotion) {
            std::cout << "granada explota\n";
            greenGrenade->explode();
            greenGrenade = NULL;
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
                                                        w->getHp(),
                                                        w->getTeamNumber());
            vectorGusanos.push_back(g);
        }

        // IF NO ESTA VIVO Y ESTA QUIETO O COLISIONANDO CONTRA LA VIGA -> LO ELIMINAS

    }
    std::shared_ptr<Gusanos> gusanos = std::make_shared<Gusanos>(vectorGusanos);

    int id = players[indexOfActualPlayer].getActualWormId(); // obtengo el id del gusano actual
    //int id = 1;
    gusanos->set_gusano_de_turno(id);

    // SI HAY GRANADA
    if (greenGrenade != NULL) {
        gusanos->set_flag_proyectil(true);
    }
    
    broadcaster.AddDtoToQueues(gusanos);
    // crear granada
    if (greenGrenade != NULL) {
        std::shared_ptr<GranadaVerde> granada = std::make_shared<GranadaVerde>((uint16_t)(greenGrenade->getXCoordinate() * 100), (uint16_t)(greenGrenade->getYCoordinate() * 100));

        broadcaster.AddDtoToQueues(granada);
    }
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
    broadcaster.AddDtoToQueues(vigas);
}


void Game::moveWormRight()
{

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    // lista de gusano = diccionario [ID];

    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->moveRight();
    // std::cout << "posicion gusano = " << world.getWorms().front()->getXCoordinate() << "\n";
}

void Game::moveWormLeft()
{

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->moveLeft();
}

void Game::jumpWorm() {
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->jump();
}

void Game::batWorm(int angle) {
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->bat(world.getWorms(), angle);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::stop()
{
    game_finished = true;
    // liberar memoria
}

void Game::throwGreenGrenade(float angle, int power, int timeToExplotion) {
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    greenGrenade = new GreenGrenade(&world.world, actualWorm->getXCoordinate(), 
                                    actualWorm->getYCoordinate(),
                                    timeToExplotion);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    greenGrenade->shoot(direction, angle, power);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::executeCommand(std::shared_ptr<Dto> dto)
{
    uint8_t clientId = dto->get_cliente_id();
    if (clientId != idTurn) return;
    uint8_t code = dto->return_code();
    if (code == MOVER_A_DERECHA_CODE)
    {
        moveWormRight(); // SI ES SU TURNO, LE PASAMOS EL ID
    }
    else if (code == MOVER_A_IZQUIERDA_CODE)
    {
        moveWormLeft(); // SI ES SU TURNO, LE PASAMOS EL ID
    }
    else if (code == BATEAR_CODE) {
        std::shared_ptr<Batear> batear = std::dynamic_pointer_cast<Batear>(dto);
        int angle = batear->get_angulo();
        batWorm(angle);
    } else if (code == SALTAR_CODE) {
        jumpWorm();
    }
    else if (code == GRANADA_VERDE_CODE) {
        std::shared_ptr<GranadaVerde> grenade = std::dynamic_pointer_cast<GranadaVerde>(dto);
        std::cout << "angulo = " << (int)grenade->get_angulo() << " potencia = " << (int)grenade->get_potencia() << "\n";
        throwGreenGrenade((float)grenade->get_angulo() * 3.14f / 180.0f, grenade->get_potencia(), grenade->get_tiempo());
    }
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
