#include "game.h"

Game::Game(Queue<Dto *> &queue, Broadcaster &broadcaster) : common_queue(queue),
                                                            broadcaster(broadcaster),
                                                            world(World()),
                                                            game_finished(false)
{
    world.addBeam(0, 9, 0, LONG);
    world.addBeam(6, 9, 0, LONG);
    world.addBeam(12, 9, 0, LONG);
    world.addBeam(18, 9, 0, LONG);
    world.addBeam(24, 9, 0, LONG);
    world.addBeam(30, 9, 0, LONG);

    world.addWorm(0, 9);
    // world.addWorm(12, 9);
}

void Game::run()
{

    while (not game_finished)
    {
        // Dto *dto;
        // bool popeo = common_queue.try_pop(dto);
        Dto *dto = common_queue.pop();
        executeCommand(dto);
        update();
        // broadcast();
    }
}

void Game::update()
{
    world.step();
}

void Game::sendWorms(Queue<Dto *> &q)
{
    for (Worm *w : world.getWorms())
    {
        std::cout << "x = " << (int)(w->getXCoordinate() * 100) << "\n";
        std::cout << "y = " << (int)(w->getYCoordinate() * 100) << "\n";
        Gusano *g = new Gusano((w->getId()),
                               (int)(w->getXCoordinate() * 100),
                               (int)(w->getYCoordinate() * 100));

        q.push(g);
    }
}

void Game::sendMap(Queue<Dto *> &q)
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
    q.push(vigas); // agrego a la cola una lista de viga
}

void Game::moveWormRight()
{
    world.getWorms().front()->moveRight();
    std::cout << "posicion gusano = " << world.getWorms().front()->getXCoordinate() << "\n";
}

void Game::stop()
{
    game_finished = true;
}

void Game::executeCommand(Dto *dto)
{
    uint8_t code = dto->return_code();
    if (code == MOVER_A_DERECHA_CODE)
    {
        moveWormRight();
        Worm *worm = world.getWorms().front();
        uint16_t x = worm->getXCoordinate() * 100;
        uint16_t y = worm->getYCoordinate() * 100;
        uint8_t id = worm->getId();
        Gusano *g = new Gusano(id, x, y);
        broadcaster.AddGusanoToQueues(g);
    }
}

void Game::broadcast()
{
}
