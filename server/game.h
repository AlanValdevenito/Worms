#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <iostream>
#include <exception>
#include <list>
#include "box2d/box2d.h"
#include "world.h"
#include "server_protocol.h"
#include "thread.h"
#include "queue.h"
#include "broadcaster.h"
#include "constantes.h"
#include "dto.h"
#include "viga.h"
#include "gusano.h"

class Game : public Thread
{
private:
    Queue<Dto *> &common_queue;
    Broadcaster &broadcaster;
    World world;
    b2Body *body_w;

    // std::map<int, LISTA DE WORMS>;

public:
    int idTurn = -1;
    bool game_finished;
    Game(Queue<Dto *> &queue, Broadcaster &broadcaster);
    void update();
    void run() override;
    void stop() override;
    void sendMap(Queue<Dto *> &q);
    void sendWorms();

    void moveWormLeft(uint8_t id);
    void moveWormRight(uint8_t id);
    void executeCommand(Dto *dto);
    void broadcast();
};
#endif
