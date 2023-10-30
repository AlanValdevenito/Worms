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
#include <list>

#include "queue.h"
// #include "broadcaster.h"
#include "receiver_thread.h"
#include "sender_thread.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"
#include "server_client.h"
#include "partida.h"
#include "partidas_lista.h"
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

private:
    std::list<ServerClient *> clients;
    Queue<Dto *> common_queue;
    Queue<Dto *> lobby_queue;
    uint8_t mapId;
    // std::list<Partida *> partidas;
    // Broadcaster broadcaster;
    Partida partida;

    void sendMatchList(ServerClient *c);
};
#endif
