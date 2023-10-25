#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket &skt) : skt(skt) {}

ServerProtocol::~ServerProtocol() {}

Dto *ServerProtocol::recv(bool &was_closed)
{
    uint8_t a;
    skt.recvall(&a, sizeof(a), &was_closed);
    printf("recibido: %u\n", a);
    return new Dto(a);
}
