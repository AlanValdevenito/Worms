#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket &skt) : skt(skt) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::sendId(std::shared_ptr<ClienteId> id, bool &was_closed)
{
    uint8_t code = id->return_code();
    skt.sendall(&(code), sizeof(code), &was_closed);

    uint8_t id_cliente = id->get_cliente_id();
    // printf("id enviado: %u\n",id_cliente );
    skt.sendall(&(id_cliente), sizeof(id_cliente), &was_closed);
}

void ServerProtocol::sendVigas(std::shared_ptr<Dto> vs, bool &was_closed)
{
    uint8_t code = vs->return_code();
    skt.sendall(&(code), sizeof(code), &was_closed); // notifico que envio una Viga

    uint8_t cant = vs->cantidad();
    skt.sendall(&(cant), sizeof(cant), &was_closed); // especifico la cantidad que llegara

    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Viga> v = std::dynamic_pointer_cast<Vigas>(vs)->popViga(i);
        sendViga(v, was_closed); // envio la viga
        // delete v;                // libero la memoria de la viga
    }
}

void ServerProtocol::sendViga(std::shared_ptr<Dto> dto, bool &was_closed)
{
    uint16_t x = htons(dto->x_pos());
    uint16_t y = htons(dto->y_pos());
    uint16_t ancho = htons(dto->return_ancho());
    uint16_t alto = htons(dto->return_alto());

    printf("x:%u  y:%u ancho:%u  alto:%u \n", x, y, ancho, alto);

    skt.sendall(&(x), sizeof(x), &was_closed);
    skt.sendall(&(y), sizeof(y), &was_closed);
    skt.sendall(&(ancho), sizeof(ancho), &was_closed);
    skt.sendall(&(alto), sizeof(alto), &was_closed);
}

void ServerProtocol::sendAllWorms(std::shared_ptr<Gusanos> gs, bool &was_closed)
{
    uint8_t code = gs->return_code();
    skt.sendall(&(code), sizeof(code), &was_closed); // notifico que envio una Viga

    uint8_t cant = gs->cantidad();
    skt.sendall(&(cant), sizeof(cant), &was_closed); // especifico la cantidad que llegara

    // printf("cantidad de gusanos a enviar %u\n", cant);
    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Gusano> g = gs->popGusano(i);
        uint8_t id = g->get_id();
        uint16_t x = htons(g->x_pos());
        uint16_t y = htons(g->y_pos());
        uint8_t vida = g->get_vida();

        printf("gusano %d)  id:%u  x:%u  y:%u \n", i, g->get_id(), g->x_pos(), g->y_pos());

        skt.sendall(&(id), sizeof(id), &was_closed);
        skt.sendall(&(x), sizeof(x), &was_closed);
        skt.sendall(&(y), sizeof(y), &was_closed);
        skt.sendall(&(vida), sizeof(vida), &was_closed); // notifico que envio un gusano

        // delete g; // Liberar memoria
    }
}

void ServerProtocol::sendWorms(std::shared_ptr<Gusano> g, bool &was_closed)
{

    uint8_t code = g->return_code();
    skt.sendall(&(code), sizeof(code), &was_closed); // notifico que envio un gusano

    uint8_t id = g->get_id();
    uint16_t x = htons(g->x_pos());
    uint16_t y = htons(g->y_pos());
    uint8_t vida = g->get_vida();

    printf("id:%u  x:%u  y:%u vida:%u \n", g->get_id(), g->x_pos(), g->y_pos(), g->get_vida());

    skt.sendall(&(id), sizeof(id), &was_closed);
    skt.sendall(&(x), sizeof(x), &was_closed);
    skt.sendall(&(y), sizeof(y), &was_closed);
    skt.sendall(&(vida), sizeof(vida), &was_closed); // notifico que envio un gusano
}

void ServerProtocol::sendPartidas(std::shared_ptr<ListaDePartidas> l, bool &was_closed)
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

void ServerProtocol::sendIniciarPartida(std::shared_ptr<Dto> dto, bool &was_closed)
{
    uint8_t code = dto->return_code();
    skt.sendall(&(code), sizeof(code), &was_closed);
}

std::shared_ptr<Dto> ServerProtocol::recvPartidaSeleccionada(uint8_t id, bool &was_closed)
{
    
    uint8_t op;
    skt.recvall(&op, sizeof(op), &was_closed);
    printf("opcion recibida: %u\n", op);
    return std::make_shared<ListaDePartidas>(id,op);
}

std::shared_ptr<Dto> ServerProtocol::recvAtaqueConBate(uint8_t id, bool &was_closed)
{
    
    uint8_t angulo;
    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    printf("angulo recibido: %u\n", angulo);
    return std::make_shared<Batear>(id,angulo);
}

std::shared_ptr<Dto> ServerProtocol::recv(bool &was_closed)
{
    uint8_t id;
    skt.recvall(&id, sizeof(id), &was_closed); 

    printf("cliente id: %u\n", id);

    uint8_t code;
    skt.recvall(&code, sizeof(code), &was_closed);

    if (code == LISTA_DE_PARTIDAS_CODE)
        return recvPartidaSeleccionada(id, was_closed);
    else if (code == MOVER_A_DERECHA_CODE)
        return std::make_shared<MoverADerecha>(id);
    else if (code == MOVER_A_IZQUERDA_CODE)
        return std::make_shared<MoverAIzquierda>(id);
    else if (code == BATEAR_CODE)
        return recvAtaqueConBate(id,was_closed);

    return std::make_shared<Dto>(code); // DEBERIA SER UN DEAD DTO
}
