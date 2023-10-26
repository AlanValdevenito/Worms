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
#include "dto.h"
#include "viga.h"

class Game : public Thread
{
private:
    Queue<Dto *> &common_queue;
    Broadcaster &broadcaster;
    World world;

public:
    bool game_finished;
    Game(Queue<Dto *> &queue, Broadcaster &broadcaster);
    void update();
    void run() override;
    void stop() override;
    void broadcast(Queue<Dto *> &q);
};
#endif