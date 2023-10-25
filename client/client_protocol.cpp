#include "client_protocol.h"

ClientProtocol::ClientProtocol(Socket &skt) : skt(skt) {}

ClientProtocol::~ClientProtocol() {}

void ClientProtocol::send(bool &was_closed)
{
    uint8_t a = 4;
    printf("enviar: %u\n", a);
    skt.sendall(&a, sizeof(a), &was_closed);
}
