#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

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
#include "dto.h"
#include "cliente_id.h"

class ServerClient
{
public:
    ServerClient(Socket &&socket, Queue<Dto *> &q, Queue<Dto *> &common_queue, uint8_t id);
    ~ServerClient();
    bool is_dead();
    void join();
    void kill();
    void start();
    void addMapToQueue();

    uint8_t id;
    Queue<Dto *> &common_queue;
    Queue<Dto *> sender_queue;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

private:
    Socket skt;
    Queue<Dto *> &lobby_queue;
    ServerProtocol serverproto;
    Receiver recv_th;
    Sender send_th;
};
#endif
