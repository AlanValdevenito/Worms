#include "game.h"
#include <chrono>
#include <thread>

#define TURN_DURATION 5

Game::Game(Queue<Dto *> &queue, Broadcaster &broadcaster) : common_queue(queue),
                                                            broadcaster(broadcaster),
                                                            world(World()),
                                                            game_finished(false)
{

    /* VIGAS */

    world.addBeam(3, 9, 0, LONG); // Ocupa del 1 al 6
    world.addBeam(9, 9, 0, LONG); // Ocupa del 7 al 12
    world.addBeam(15, 9, 0, LONG); // Ocupa del 13 al 18
    world.addBeam(21, 9, 0, LONG); // Ocupa del 19 al 24

    /* AGUA */

    // world.addBeam(0, 0, 0, LONG);
    // world.addBeam(6, 0, 0, LONG);
    // world.addBeam(12, 0, 0, LONG);

    /* WORMS */

    world.addWorm(3, 10);
    world.addWorm(15, 10);
}

void Game::run()
{   
    //int idFirstWorm = world.getWorms().front().getId();
    //int idSecondWorm = world.getWorms().back().getId();
    //idTurn = idFirstWorm;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //std::chrono::steady_clock::time_point end;
    while (not game_finished)
    {   
        Dto *dto;
        if (common_queue.try_pop(dto)) {
            executeCommand(dto);
        }
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        //end = std::chrono::steady_clock::now();
        /*if (std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() >= TURN_DURATION) {
            std::cout << "pasaron " << TURN_DURATION << " segundos, cambio de turno\n";
            begin = std::chrono::steady_clock::now();
            if (idTurn == idFirstWorm) {
                idTurn = idSecondWorm;
            } else if (idTurn == idSecondWorm) {
                idTurn = idFirstWorm;
            }
        }*/
        // broadcast();
    }
}

void Game::update()
{   
    world.step();
    /*Worm *worm = world.getWorms().front();
    uint16_t x = worm->getXCoordinate() * 100;
    uint16_t y = worm->getYCoordinate() * 100;
    uint8_t id = worm->getId();
    Gusano *g = new Gusano(id, x, y);
    broadcaster.AddGusanoToQueues(g);*/
}

void Game::sendWorms()
{ 

    std::list<Gusano *> listaGusanos;
    for (Worm w : world.getWorms())
    {
        Gusano *g = new Gusano((w.getId()),
                               (int)(w.getXCoordinate() * 100),
                               (int)(w.getYCoordinate() * 100));

        listaGusanos.push_back(g);

    }
    Gusanos *gusanos = new Gusanos(listaGusanos);
    broadcaster.AddGusanosToQueues(gusanos);
}

void Game::sendMap()
{
    std::list<Viga *> vs;
    // por cada viga manda un Dto Viga a los senders
    for (auto &beam : world.getBeams())
    {
        // cambiar los parametros a float
        Viga *viga = new Viga((int)(beam.getXCoordinate() * 100),
                              (int)(beam.getYCoordinate() * 100),
                              (int)(beam.getWidth() * 100),
                              (int)(beam.getHeight() * 100));

        vs.push_back(viga);
    }
    Vigas *vigas = new Vigas(vs);
    //q.push(vigas); // agrego a la cola una lista de viga
    broadcaster.AddVigasToQueues(vigas);
}

void Game::moveWormRight(uint8_t id)
{   

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    // lista de gusano = diccionario [ID];

    for (Worm worm : world.getWorms()) {
        if (worm.getId() == id) {
            worm.moveRight();
        }
    }
    //std::cout << "posicion gusano = " << world.getWorms().front()->getXCoordinate() << "\n";
}

void Game::moveWormLeft(uint8_t id) {

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    for (Worm worm : world.getWorms()) {
        if (worm.getId() == id) {
            worm.moveLeft();
        }
    }
}

void Game::stop()
{
    game_finished = true;
}

void Game::executeCommand(Dto *dto)
{
    uint8_t clientId = dto->get_cliente_id();

    uint8_t code = dto->return_code();
    if (code == MOVER_A_DERECHA_CODE)
    {
        moveWormRight(clientId); // SI ES SU TURNO, LE PASAMOS EL ID
        
    } else if (code == MOVER_A_IZQUERDA_CODE) {
        moveWormLeft(clientId); // SI ES SU TURNO, LE PASAMOS EL ID
    }

    for (Worm worm : world.getWorms()) {
        if (worm.getId() == clientId) {
            uint16_t x = worm.getXCoordinate() * 100;
            uint16_t y = worm.getYCoordinate() * 100;
            uint8_t id = worm.getId();
            Gusano *g = new Gusano(id, x, y);
            broadcaster.AddGusanoToQueues(g);
        }
    }
    delete dto;
}

void Game::broadcast()
{
}
