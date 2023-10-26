#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket &skt) : skt(skt) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::sendViga(Dto *dto, bool &was_closed)
{
    uint8_t x = dto->x_pos();
    uint8_t y = dto->y_pos();
    uint8_t alto = dto->return_alto();
    uint8_t ancho = dto->return_ancho();

    skt.sendall(&(x), sizeof(x), &was_closed);
    skt.sendall(&(y), sizeof(y), &was_closed);
    skt.sendall(&(ancho), sizeof(ancho), &was_closed);
    skt.sendall(&(alto), sizeof(alto), &was_closed);
}

Dto *ServerProtocol::recv(bool &was_closed)
{
    uint8_t a;
    skt.recvall(&a, sizeof(a), &was_closed);
    printf("recibido: %u\n", a);
    return new Dto(a);
}
