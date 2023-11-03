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

    /* AGUA */

    // world.addBeam(0, 0, 0, LONG);
    // world.addBeam(6, 0, 0, LONG);
    // world.addBeam(12, 0, 0, LONG);

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
            executeCommand(dto);
        }
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(32));
    
        // broadcast();
    }
}

void Game::passTurn() {
    // cambio de turno 
    end = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() >= TURN_DURATION) {
        std::cout << "pasaron " << TURN_DURATION << " segundos, cambio de turno\n";
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
    sendWorms();
    /*for (Worm worm : world.getWorms()) {
        if (worm.isRunning) {
            uint16_t x = worm.getXCoordinate() * 100;
            uint16_t y = worm.getYCoordinate() * 100;
            uint8_t id = worm.getId();
            std::shared_ptr<Gusano> g = std::make_shared<Gusano>(id, x, y);
            broadcaster.AddGusanoToQueues(g);
        }
    }*/
    /*Worm *worm = world.getWorms().front();
    uint16_t x = worm->getXCoordinate() * 100;
    uint16_t y = worm->getYCoordinate() * 100;
    uint8_t id = worm->getId();
    Gusano *g = new Gusano(id, x, y);
    broadcaster.AddGusanoToQueues(g);*/
}

void Game::sendWorms()
{

    std::vector<std::shared_ptr<Gusano>> vectorGusanos;
    for (Worm *w : world.getWorms())
    {
        std::shared_ptr<Gusano> g = std::make_shared<Gusano>((w->getId()),
                                                             (int)(w->getXCoordinate() * 100),
                                                             (int)(w->getYCoordinate() * 100),
                                                             w->getHp());
        vectorGusanos.push_back(g);
    }
    std::shared_ptr<Gusanos> gusanos = std::make_shared<Gusanos>(vectorGusanos);
    broadcaster.AddGusanosToQueues(gusanos);
}

// void Game::sendWorms()
// {

//     std::list<Gusano *> listaGusanos;
//     for (Worm w : world.getWorms())
//     {
//         Gusano *g = new Gusano((w.getId()),
//                                (int)(w.getXCoordinate() * 100),
//                                (int)(w.getYCoordinate() * 100));

//         listaGusanos.push_back(g);

//     }
//     Gusanos *gusanos = new Gusanos(listaGusanos);
//     broadcaster.AddGusanosToQueues(gusanos);
// }

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
                                                            (int)(beam.getHeight() * 100));
        vs.push_back(viga);
    }
    std::shared_ptr<Vigas> vigas = std::make_shared<Vigas>(vs);
    broadcaster.AddVigasToQueues(vigas);
}

// void Game::sendMap()
// {
//     std::list<Viga *> vs;
//     // por cada viga manda un Dto Viga a los senders
//     for (auto &beam : world.getBeams())
//     {
//         // cambiar los parametros a float
//         Viga *viga = new Viga((int)(beam.getXCoordinate() * 100),
//                               (int)(beam.getYCoordinate() * 100),
//                               (int)(beam.getWidth() * 100),
//                               (int)(beam.getHeight() * 100));

//         vs.push_back(viga);
//     }
//     Vigas *vigas = new Vigas(vs);
//     // q.push(vigas); // agrego a la cola una lista de viga
//     broadcaster.AddVigasToQueues(vigas);
// }

void Game::moveWormRight(uint8_t id)
{

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    // lista de gusano = diccionario [ID];

    int idActualWorm = players[idTurn - 1].getActualWormId();
    //std::cout << "actual worm = " << idActualWorm << "\n";
    for (Worm *worm : world.getWorms()) {
        if (worm->getId() == idActualWorm) {
            worm->moveRight();
        }
    }
    // std::cout << "posicion gusano = " << world.getWorms().front()->getXCoordinate() << "\n";
}

void Game::moveWormLeft(uint8_t id)
{

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    int idActualWorm = players[idTurn - 1].getActualWormId();
    for (Worm *worm : world.getWorms()) {
        if (worm->getId() == idActualWorm) {
            worm->moveLeft();
        }
    }
}

void Game::batWorm(uint8_t id) {
    int idActualWorm = players[idTurn - 1].getActualWormId();
    for (Worm *worm : world.getWorms()) {
        if (worm->getId() == idActualWorm) {
            worm->bat(world.getWorms());
        }
    }
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

void Game::broadcast()
{
}
