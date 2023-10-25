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

const char CHAT[] = "Chat";
const char READ[] = "Read";
const char EXIT[] = "Exit";

#include "client_protocol.h"
#include "dto.h"
#include "socket.h"

class Client
{
public:
    explicit Client(Socket &&socket);
    ~Client();
    void start();

private:
    Socket skt;
    ClientProtocol protocolo;
    bool was_closed;
};
#endif
