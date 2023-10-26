#include "game.h"

Game::Game(Queue<Dto *> &queue, Broadcaster &broadcaster) : common_queue(queue),
                                                            broadcaster(broadcaster),
                                                            world(World()),
                                                            game_finished(false)
{
    world.addBeam(0, 9, 6, 0.8);
}

void Game::run()
{

    while (not game_finished)
    {
        // dto = common_queue.try_pop();
        // execute_command(dto);
        update();
        // broadcast();
    }
}

void Game::update()
{
    world.step();
}

void Game::broadcast(Queue<Dto *> &q)
{
    // por cada viga manda un Dto Viga a los senders
    for (auto &beam : world.getBeams())
    {
        // cambiar los parametros a float
        Viga *viga = new Viga((int)(beam.getXCoordinate() * 100),
                              (int)(beam.getYCoordinate() * 100),
                              (int)(beam.getWidth() * 100),
                              (int)(beam.getHeight() * 100));
        q.push(viga);
    }
    // broadcaster.addVigaToQueues(viga);
}

void Game::stop()
{
    game_finished = true;
}