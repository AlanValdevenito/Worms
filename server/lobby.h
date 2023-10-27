#ifndef LOBBY_H
#define LOBBY_H

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

class Lobby
{
public:
    Lobby();
    ~Lobby();
    void kill();
    void reap_dead();
    void newClient(Socket &&s);

    std::list<ServerClient *> clients;

private:
    Broadcaster broadcaster;
    Queue<Dto *> common_queue;
    Game game;
};
#endif
