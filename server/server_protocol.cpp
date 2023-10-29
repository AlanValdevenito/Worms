#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket &skt) : skt(skt) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::sendVigas(Dto *vs, bool &was_closed)
{
    uint8_t code = vs->return_code();
    skt.sendall(&(code), sizeof(code), &was_closed); // notifico que envio una Viga

    uint8_t cant = vs->cantidad();
    skt.sendall(&(cant), sizeof(cant), &was_closed); // especifico la cantidad que llegara

    for (int i = 0; i < cant; i++)
    {
        Viga *v = (Viga *)vs->popViga();
        sendViga(v, was_closed); // envio la viga
        delete v;                // libero la memoria de la viga
    }
}

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

void ServerProtocol::sendWorms(Gusano *g, bool &was_closed)
{

    uint8_t code = g->return_code();
    skt.sendall(&(code), sizeof(code), &was_closed); // notifico que envio un gusano

    uint8_t id = g->get_id();
    uint16_t x = htons(g->x_pos());
    uint16_t y = htons(g->y_pos());

    // printf("id:%u  x:%u  y:%u \n", g->get_id(), g->x_pos(), g->y_pos());

    skt.sendall(&(id), sizeof(id), &was_closed);
    skt.sendall(&(x), sizeof(x), &was_closed);
    skt.sendall(&(y), sizeof(y), &was_closed);
}

void ServerProtocol::sendPartidas(ListaDePartidas *l, bool &was_closed)
{
    uint8_t code = l->return_code();
    skt.sendall(&(code), sizeof(code), &was_closed);

    std::list<uint8_t> lista = l->return_list();

    // uint8_t cant = vs->cantidad();
    // skt.sendall(&(cant), sizeof(cant), &was_closed); // cuantas opciones envio

    for (uint8_t o : lista)
    {
        printf("opcion: %u\n", o);
        skt.sendall(&(o), sizeof(o), &was_closed);
    }
}

Dto *ServerProtocol::recv(bool &was_closed)
{
    uint8_t code;
    skt.recvall(&code, sizeof(code), &was_closed);
    // printf("recibido: %u\n", a);

    if (code == LISTA_DE_PARTIDAS_CODE)
    {
        uint8_t op;
        skt.recvall(&op, sizeof(op), &was_closed);
        return new ListaDePartidas(op);
    }

    return new Dto(code);
}
