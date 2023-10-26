#include "client_protocol.h"

ClientProtocol::ClientProtocol(Socket &skt) : skt(skt) {}

ClientProtocol::~ClientProtocol() {}

void ClientProtocol::send(bool &was_closed)
{
    // uint8_t a = 4;
    // // printf("enviar: %u\n", a);
    // skt.sendall(&a, sizeof(a), &was_closed);
}

// ACA SE HACE LA SEPARACION MEDIANTE EL CODIGO QUE RECIBO PRIMERO
// Dto *ClientProtocol::receive(bool &was_closed)

Dto *ClientProtocol::receiveViga(bool &was_closed)
{
    uint16_t x;
    uint16_t y;
    uint16_t ancho;
    uint16_t alto;

    skt.recvall(&x, sizeof(x), &was_closed);
    skt.recvall(&y, sizeof(y), &was_closed);
    skt.recvall(&ancho, sizeof(ancho), &was_closed);
    skt.recvall(&alto, sizeof(alto), &was_closed);

    x = ntohs(x);
    y = ntohs(y);
    ancho = ntohs(ancho);
    alto = ntohs(alto);

    printf("Cliente ---> x:%u  y:%u ancho:%u  alto:%u  \n", x, y, ancho, alto);

    return new Viga(x, y, ancho, alto);
}