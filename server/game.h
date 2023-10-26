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
#include "blockingqueue.h"
#include "broadcaster.h"
#include "dto.h"
#include "viga.h"

class Game : public Thread
{
private:
    BlockingQueue &common_queue;
    Broadcaster &broadcaster;
    World world;

public:
    bool game_finished;
    Game(BlockingQueue &queue, Broadcaster &broadcaster);
    void update();
    void run() override;
    void stop() override;
    void broadcast(BlockingQueue &q);
};
#endif