#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket &skt) : skt(skt) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::sendViga(Dto *dto, bool &was_closed)
{
    uint16_t x = htons(dto->x_pos());
    uint16_t y = htons(dto->y_pos());
    uint16_t ancho = htons(dto->return_ancho());
    uint16_t alto = htons(dto->return_alto());

    // printf("x:%u  y:%u ancho:%u  alto:%u \n", x, y, ancho, alto);

    skt.sendall(&(x), sizeof(x), &was_closed);
    skt.sendall(&(y), sizeof(y), &was_closed);
    skt.sendall(&(ancho), sizeof(ancho), &was_closed);
    skt.sendall(&(alto), sizeof(alto), &was_closed);
}

Dto *ServerProtocol::recv(bool &was_closed)
{
    uint8_t a;
    skt.recvall(&a, sizeof(a), &was_closed);
    // printf("recibido: %u\n", a);
    return new Dto(a);
}
