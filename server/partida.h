#ifndef PARTIDA_H
#define PARTIDA_H

#include <atomic>
#include <chrono>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "queue.h"
#include "broadcaster.h"
#include "receiver_thread.h"
#include "sender_thread.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"
#include "server_client.h"
#include "game.h"
#include "dto.h"

class Partida
{
public:
    Partida(Queue<Dto *> &cq);
    ~Partida();
    void start(ServerClient *c);
    void finish();

private:
    Broadcaster broadcaster;
    Queue<Dto *> &common_queue;
    Game game;
};
#endif
