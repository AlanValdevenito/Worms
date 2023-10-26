#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <netinet/in.h>

#include "blockingqueue.h"
#include "dto.h"
#include "socket.h"

class ServerProtocol
{
public:
    explicit ServerProtocol(Socket &skt);
    ~ServerProtocol();
    Dto *recv(bool &was_closed);
    void sendViga(Dto *dto, bool &was_closed);

private:
    Socket &skt;
    // Dto *recv_message(bool &was_closed, uint16_t sz, uint8_t code);
};
#endif
