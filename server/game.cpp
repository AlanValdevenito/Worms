#include "game.h"


Game::Game(BlockingQueue& queue, Broadcaster& broadcaster) :
    common_queue(queue),
    broadcaster(broadcaster),
    world(World()),
    game_finished(false) {
        world.addBeam(3, 0, 6, 0.8);
    }

void Game::run() {

    while (not game_finished) {
        // dto = common_queue.try_pop();
        // execute_command(dto);
        update();
        broadcast();
    }
}

void Game::update() {
    world.step();
}

void Game::broadcast() {
    // por cada viga manda un Dto Viga a los senders
    for (auto& beam: world.getBeams()) {
        // cambiar los parametros a float
        Viga *viga = new Viga((int)beam.getXCoordinate(),
                              (int)beam.getYCoordinate(),
                              (int)beam.getWidth(),
                              (int)beam.getHeight());
        broadcaster.addMessageToQueues(viga);
    } 
}

void Game::stop() {
    game_finished = true;
}