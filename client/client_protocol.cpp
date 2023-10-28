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
Dto *ClientProtocol::receive(bool &was_closed)
{
    uint8_t code;
    skt.recvall(&code, sizeof(code), &was_closed);

    if (code == VIGAS_CODE)
        return receiveVigas(was_closed);
    else if (code == GUSANO_CODE)
        return receiveGusano(was_closed);
    else
        std::cerr << "Codigo recibido sin identificar\n";

    return new DeadDto();
}

Dto *ClientProtocol::receiveVigas(bool &was_closed)
{
    uint8_t cant;
    skt.recvall(&cant, sizeof(cant), &was_closed);

    std::list<Viga *> vs;
    for (int i = 0; i < cant; i++)
    {
        Viga *v = (Viga *)receiveViga(was_closed);
        vs.push_back(v);
    }
    return new Vigas(vs);
}

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

    // printf("Cliente ---> x:%u  y:%u ancho:%u  alto:%u  \n", x, y, ancho, alto);

    return new Viga(x, y, ancho, alto);
}

Dto *ClientProtocol::receiveGusano(bool &was_closed)
{
    uint8_t id;
    uint16_t x;
    uint16_t y;

    skt.recvall(&id, sizeof(id), &was_closed);
    skt.recvall(&x, sizeof(x), &was_closed);
    skt.recvall(&y, sizeof(y), &was_closed);

    x = ntohs(x);
    y = ntohs(y);

    // printf("Cliente ---> id:%u  x:%u y:%u  \n", id, x, y);

    return new Gusano(id, x, y);
}

void ClientProtocol::moverADerecha(MoverADerecha *m, bool &was_closed)
{
    uint8_t code = m->return_code();
    // printf("enviar: %u\n", a);
    skt.sendall(&code, sizeof(code), &was_closed);
}
