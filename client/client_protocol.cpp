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
std::shared_ptr<Dto> ClientProtocol::receive(bool &was_closed)
{
    uint8_t code;
    skt.recvall(&code, sizeof(code), &was_closed);

    if (code == VIGA_CODE)
        return receiveVigas(was_closed);
    else if (code == GUSANO_CODE)
        return receiveGusano(was_closed);
    else if (code == GUSANOS_CODE)
        return receiveGusanos(was_closed);
    else if (code == LISTA_DE_PARTIDAS_CODE)
        return receivePartidas(was_closed);
    else if (code == CLIENTE_ID_CODE)
        return receiveId(was_closed);
    else if (code == INICIAR_PARIDA)
        return std::make_shared<Dto>(INICIAR_PARIDA);
    else
        std::cerr << "Codigo recibido sin identificar\n";

    // return new DeadDto();
    return std::make_shared<DeadDto>();
}

std::shared_ptr<Dto> ClientProtocol::receiveId(bool &was_closed)
{
    uint8_t id;
    skt.recvall(&id, sizeof(id), &was_closed);
    // printf("id recibido: %u\n",id );
    // return new ClienteId(id);
    return std::make_shared<ClienteId>(id);
}

std::shared_ptr<Dto> ClientProtocol::receivePartidas(bool &was_closed)
{
    uint8_t op1;
    skt.recvall(&op1, sizeof(op1), &was_closed);
    uint8_t op2;
    skt.recvall(&op2, sizeof(op2), &was_closed);

    printf("op1: %u    op2: %u \n", op1, op2);

    // std::shared_ptr<ListaDePartidas> l = new ListaDePartidas();
    std::shared_ptr<ListaDePartidas> l = std::make_shared<ListaDePartidas>();
    l->addOption(op1);
    l->addOption(op2);
    return l;
}

std::shared_ptr<Dto> ClientProtocol::receiveVigas(bool &was_closed)
{
    uint8_t cant;
    skt.recvall(&cant, sizeof(cant), &was_closed);

    std::vector<std::shared_ptr<Viga>> vs;
    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Viga> v = receiveViga(was_closed);
        vs.push_back(v);
    }
    // return new Vigas(vs);
    return std::make_shared<Vigas>(vs);
}

std::shared_ptr<Viga> ClientProtocol::receiveViga(bool &was_closed)
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

    // return new Viga(x, y, ancho, alto);
    return std::make_shared<Viga>(x, y, ancho, alto);
}

std::shared_ptr<Dto> ClientProtocol::receiveGusanos(bool &was_closed)
{
    uint8_t cant;
    skt.recvall(&cant, sizeof(cant), &was_closed);

    std::vector<std::shared_ptr<Gusano>> lista;
    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Gusano> g = (std::shared_ptr<Gusano>)receiveGusano(was_closed);
        printf("gusano %d)  id:%u  x:%u  y:%u \n", i, g->get_id(), g->x_pos(), g->y_pos());
        lista.push_back(g);
    }
    // return new Gusanos(lista);
    return std::make_shared<Gusanos>(lista);
}

std::shared_ptr<Gusano> ClientProtocol::receiveGusano(bool &was_closed)
{
    uint8_t id;
    uint16_t x;
    uint16_t y;

    skt.recvall(&id, sizeof(id), &was_closed);
    skt.recvall(&x, sizeof(x), &was_closed);
    skt.recvall(&y, sizeof(y), &was_closed);

    x = ntohs(x);
    y = ntohs(y);

    printf("Cliente ---> id:%u  x:%u y:%u  \n", id, x, y);

    // return new Gusano(id, x, y);
    return std::make_shared<Gusano>(id, x, y);
}

void ClientProtocol::moverADerecha(std::shared_ptr<MoverADerecha> m, bool &was_closed)
{
    uint8_t id_cliente = m->get_cliente_id();
    skt.sendall(&id_cliente, sizeof(id_cliente), &was_closed);

    uint8_t code = m->return_code();
    // printf("enviar: %u\n", a);
    skt.sendall(&code, sizeof(code), &was_closed);
}

void ClientProtocol::moverAIzquierda(std::shared_ptr<MoverAIzquierda> m, bool &was_closed)
{
    uint8_t id_cliente = m->get_cliente_id();
    skt.sendall(&id_cliente, sizeof(id_cliente), &was_closed);

    uint8_t code = m->return_code();
    // printf("enviar: %u\n", a);
    skt.sendall(&code, sizeof(code), &was_closed);
}

void ClientProtocol::enviarSeleccion(std::shared_ptr<ListaDePartidas> l, bool &was_closed)
{
     uint8_t id_cliente = l->get_cliente_id();
    skt.sendall(&id_cliente, sizeof(id_cliente), &was_closed);

    uint8_t code = l->return_code();
    // printf("enviar: %u\n", a);
    skt.sendall(&code, sizeof(code), &was_closed);

    uint8_t opcion = l->seleccionada;
    printf("enviar opcion: %u\n", opcion);
    skt.sendall(&opcion, sizeof(opcion), &was_closed);
}
