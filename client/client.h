#ifndef CLIENT_CLASS_H
#define CLIENT_CLASS_H

#include <chrono>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <memory>

#include "client_protocol.h"
#include "client_receiver.h"
#include "broadcaster.h"
#include "client_sender.h"
#include "dto.h"
#include "socket.h"
#include "queue.h"

class Client
{
public:
    explicit Client(Socket &&socket);
    ~Client();
    void start();
    void kill();
    void servidorCerro();
    void join();
    uint8_t id;
    Queue<std::shared_ptr<Dto>> send_queue;
    Queue<std::shared_ptr<Dto>> recv_queue;

private:
    Socket skt;
    ClientProtocol protocolo;
    bool was_closed;
    ReceiverTH recv_th;
    SenderTH send_th;
};
#endif
