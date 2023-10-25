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

#include "blockingqueue.h"
#include "broadcaster.h"
#include "receiver_thread.h"
#include "sender_thread.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"

class ServerClient
{
public:
    ServerClient(Socket &&socket, Broadcaster &b, BlockingQueue &q);
    ~ServerClient();
    bool is_dead();
    void join();
    void kill();
    void start();
    void addMapToQueue();

    BlockingQueue &common_queue;
    BlockingQueue sender_queue;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

private:
    Socket skt;
    Broadcaster &broadcaster;
    ServerProtocol serverproto;
    Receiver recv_th;
    Sender send_th;
};
#endif
