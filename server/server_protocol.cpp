#include "server_protocol.h"

// ServerProtocol::ServerProtocol(Socket &skt) : skt(skt) {}
ServerProtocol::ServerProtocol(SocketInterface *skt) : skt(skt) {}

ServerProtocol::~ServerProtocol() {}

bool ServerProtocol::enviarCodigoDeElemento(std::shared_ptr<Dto> dto, bool &was_closed)
{
    uint8_t code = dto->return_code();
    skt->sendall(&(code), sizeof(code), &was_closed);

    // printf("codigo : %u\n", code);
    return !was_closed;
}

bool ServerProtocol::enviarId(std::shared_ptr<ClienteId> id, bool &was_closed)
{
    if (not enviarCodigoDeElemento(id, was_closed))
        return false;

    uint8_t id_cliente = id->get_cliente_id();
    // printf("id enviado: %u\n", id_cliente);
    skt->sendall(&(id_cliente), sizeof(id_cliente), &was_closed);

    return !was_closed;
}

bool ServerProtocol::enviarVigas(std::shared_ptr<Dto> vs, bool &was_closed)
{
    if (not enviarCodigoDeElemento(vs, was_closed))
        return false;

    uint8_t cant = vs->cantidad();
    skt->sendall(&(cant), sizeof(cant), &was_closed); // especifico la cantidad que llegara
    if (was_closed)
        return false;

    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Viga> v = std::dynamic_pointer_cast<Vigas>(vs)->popViga(i);
        if (not enviarViga(v, was_closed)) // envio la viga
            return false;                  // ESTA BIENN??    <-------------------------------
    }

    return true;
}

bool ServerProtocol::enviarViga(std::shared_ptr<Dto> dto, bool &was_closed)
{
    uint16_t x = htons(dto->x_pos());
    uint16_t y = htons(dto->y_pos());
    uint16_t ancho = htons(dto->return_ancho());
    uint16_t alto = htons(dto->return_alto());
    uint16_t angulo = htons(dto->return_angulo());

    skt->sendall(&(x), sizeof(x), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(y), sizeof(y), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(ancho), sizeof(ancho), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(alto), sizeof(alto), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(angulo), sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    // printf("Server ---> x:%u  y:%u ancho:%u  alto:%u  angulo:%u  \n", dto->x_pos(), dto->y_pos(), dto->return_ancho(), dto->return_alto(), dto->return_angulo());

    return true;
}

bool ServerProtocol::enviarDatosDelGusano(std::shared_ptr<Gusano> g, bool &was_closed)
{
    uint8_t id = g->get_id();
    uint16_t x = htons(g->x_pos());
    uint16_t y = htons(g->y_pos());
    uint8_t vida = g->get_vida();
    uint8_t color = g->get_color();

    skt->sendall(&(id), sizeof(id), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(x), sizeof(x), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(y), sizeof(y), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(vida), sizeof(vida), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(color), sizeof(color), &was_closed);
    if (was_closed)
        return false;

    // printf("id:%u  x:%u  y:%u vida:%u color:%u\n", g->get_id(), g->x_pos(), g->y_pos(), g->get_vida(), g->get_color());
    return true;
}

bool ServerProtocol::enviarListaDeGusanos(std::shared_ptr<Gusanos> gs, bool &was_closed)
{
    if (not enviarCodigoDeElemento(gs, was_closed))
        return false;

    uint8_t cant = gs->cantidad();
    skt->sendall(&(cant), sizeof(cant), &was_closed); // especifico la cantidad que llegara
    if (was_closed)
        return false;

    uint8_t turno = gs->get_gusano_de_turno();
    skt->sendall(&(turno), sizeof(turno), &was_closed); // especifico la cantidad que llegara
    if (was_closed)
        return false;

    uint8_t flag = gs->get_flag_proyectil();
    skt->sendall(&(flag), sizeof(flag), &was_closed); // especifico la cantidad que llegara
    if (was_closed)
        return false;

    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Gusano> g = gs->popGusano(i);
        if (not enviarDatosDelGusano(g, was_closed))
            return false;
    }
    return true;
}

bool ServerProtocol::enviarGusano(std::shared_ptr<Gusano> g, bool &was_closed)
{

    if (not enviarCodigoDeElemento(g, was_closed))
        return false;

    return enviarDatosDelGusano(g, was_closed);
}

bool ServerProtocol::enviarListaDePartidas(std::shared_ptr<ListaDePartidas> l, bool &was_closed)
{
    if (not enviarCodigoDeElemento(l, was_closed))
        return false;

    std::list<uint8_t> lista = l->return_list();

    uint8_t cant = lista.size();
    skt->sendall(&(cant), sizeof(cant), &was_closed); // cuantas opciones envio

    for (uint8_t o : lista)
    {
        // printf("opcion: %u\n", o);
        skt->sendall(&(o), sizeof(o), &was_closed);
        if (was_closed)
            return false;
    }
    return true;
}

bool ServerProtocol::enviarIniciarPartida(std::shared_ptr<Dto> dto, bool &was_closed)
{
    return enviarCodigoDeElemento(dto, was_closed);
}

bool ServerProtocol::enviarFinalizarPartida(std::shared_ptr<Dto> dto, bool &was_closed)
{
    return enviarCodigoDeElemento(dto, was_closed);
}

bool ServerProtocol::enviarTrayectoriaDeGranadaVerde(std::shared_ptr<GranadaVerde> g, bool &was_closed)
{
    if (not enviarCodigoDeElemento(g, was_closed))
        return false;

    // envio coordenadas
    uint16_t x = htons(g->x_pos());
    uint16_t y = htons(g->y_pos());
    uint8_t angulo = g->get_angulo();

    skt->sendall(&(x), sizeof(x), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(y), sizeof(y), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(angulo), sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria ---> x:%u y:%u \n", g->x_pos(), g->y_pos());

    return true;
}

bool ServerProtocol::enviarTrayectoriaDeGranadaBanana(std::shared_ptr<GranadaBanana> g, bool &was_closed)
{
    if (not enviarCodigoDeElemento(g, was_closed))
        return false;

    // envio coordenadas
    uint16_t x = htons(g->x_pos());
    uint16_t y = htons(g->y_pos());

    skt->sendall(&(x), sizeof(x), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(y), sizeof(y), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria ---> x:%u y:%u \n", g->x_pos(), g->y_pos());

    return true;
}

bool ServerProtocol::enviarTrayectoriaDeGranadaSanta(std::shared_ptr<GranadaSanta> g, bool &was_closed)
{
    if (not enviarCodigoDeElemento(g, was_closed))
        return false;

    // envio coordenadas
    uint16_t x = htons(g->x_pos());
    uint16_t y = htons(g->y_pos());

    skt->sendall(&(x), sizeof(x), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(y), sizeof(y), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria ---> x:%u y:%u \n", g->x_pos(), g->y_pos());

    return true;
}

bool ServerProtocol::enviarTrayectoriaDeDinamita(std::shared_ptr<Dinamita> g, bool &was_closed)
{
    if (not enviarCodigoDeElemento(g, was_closed))
        return false;

    // envio coordenadas
    uint16_t x = htons(g->x_pos());
    uint16_t y = htons(g->y_pos());

    skt->sendall(&(x), sizeof(x), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(y), sizeof(y), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria ---> x:%u y:%u \n", g->x_pos(), g->y_pos());

    return true;
}

bool ServerProtocol::enviarTrayectoriaDeBazuka(std::shared_ptr<Bazuka> b, bool &was_closed)
{
    if (not enviarCodigoDeElemento(b, was_closed))
        return false;

    // envio coordenadas
    uint16_t x = htons(b->x_pos());
    uint16_t y = htons(b->y_pos());
    uint8_t angulo = b->get_angulo();
    uint8_t direccion = b->get_direccion();

    skt->sendall(&(x), sizeof(x), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(y), sizeof(y), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(angulo), sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(direccion), sizeof(direccion), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria BAZUKA---> x:%u y:%u \n", b->x_pos(), b->y_pos());

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Dto> ServerProtocol::recibirPartidaSeleccionada(uint8_t id, bool &was_closed)
{
    uint8_t op;
    skt->recvall(&op, sizeof(op), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("opcion recibida: %u\n", op);
    return std::make_shared<ListaDePartidas>(id, op);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConBate(uint8_t id, bool &was_closed)
{
    uint8_t angulo;
    skt->recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("angulo recibido: %u\n", angulo);
    return std::make_shared<Batear>(id, angulo);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConGranadaVerde(uint8_t id, bool &was_closed)
{
    uint8_t potencia;
    skt->recvall(&potencia, sizeof(potencia), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t angulo;
    skt->recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t tiempo;
    skt->recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("angulo recibido: %u\n", angulo);
    return std::make_shared<GranadaVerde>(id, potencia, angulo, tiempo);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConGranadaBanana(uint8_t id, bool &was_closed)
{
    uint8_t potencia;
    skt->recvall(&potencia, sizeof(potencia), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t angulo;
    skt->recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t tiempo;
    skt->recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("angulo recibido: %u\n", angulo);
    return std::make_shared<GranadaBanana>(id, potencia, angulo, tiempo);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConGranadaSanta(uint8_t id, bool &was_closed)
{
    uint8_t potencia;
    skt->recvall(&potencia, sizeof(potencia), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t angulo;
    skt->recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t tiempo;
    skt->recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("angulo recibido: %u\n", angulo);
    return std::make_shared<GranadaSanta>(id, potencia, angulo, tiempo);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConDinamita(uint8_t id, bool &was_closed)
{
    uint8_t tiempo;
    skt->recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("angulo recibido: %u\n", angulo);
    return std::make_shared<Dinamita>(id, tiempo);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConBazuka(uint8_t id, bool &was_closed)
{
    uint8_t potencia;
    skt->recvall(&potencia, sizeof(potencia), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t angulo;
    skt->recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("%u %u \n",potencia, angulo);
    return std::make_shared<Bazuka>(id, potencia, angulo);
}

std::shared_ptr<Dto> ServerProtocol::recibirParametrosDeLaPartida(bool &was_closed)
{
    uint8_t cantidad_de_jugadores;
    skt->recvall(&cantidad_de_jugadores, sizeof(cantidad_de_jugadores), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("jugadores recibido: %u\n", cantidad_de_jugadores);
    return std::make_shared<NuevaPartida>(cantidad_de_jugadores);
}

std::shared_ptr<Dto> ServerProtocol::recibirActividad(bool &was_closed)
{
    uint8_t id;
    uint8_t code;

    skt->recvall(&id, sizeof(id), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("cliente id: %u\n", id);

    skt->recvall(&code, sizeof(code), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();
    // printf("codigo: %u\n", code);

    if (code == LISTA_DE_PARTIDAS_CODE)
        return recibirPartidaSeleccionada(id, was_closed);
    else if (code == MOVER_A_DERECHA_CODE)
        return std::make_shared<MoverADerecha>(id);
    else if (code == MOVER_A_IZQUIERDA_CODE)
        return std::make_shared<MoverAIzquierda>(id);
    else if (code == BATEAR_CODE)
        return recibirAtaqueConBate(id, was_closed);
    else if (code == FINALIZAR_CODE)
        return std::make_shared<Dto>(FINALIZAR_CODE, id);
    else if (code == SALTAR_CODE)
        return std::make_shared<Saltar>(id);
    else if (code == NUEVA_PARTIDA_CODE)
        return recibirParametrosDeLaPartida(was_closed);
    else if (code == GRANADA_VERDE_CODE)
        return recibirAtaqueConGranadaVerde(id, was_closed);
    else if (code == BAZUKA_CODE)
        return recibirAtaqueConBazuka(id, was_closed);
    else if (code == GRANADA_BANANA_CODE)
        return recibirAtaqueConGranadaBanana(id, was_closed);
    else if (code == GRANADA_SANTA_CODE)
        return recibirAtaqueConGranadaSanta(id, was_closed);
    else if (code == DINAMITA_CODE)
        return recibirAtaqueConDinamita(id, was_closed);

    return std::make_shared<DeadDto>();
}
