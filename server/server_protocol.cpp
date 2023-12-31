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

bool ServerProtocol::enviarPosicionDelElemento(std::shared_ptr<Dto> dto, bool &was_closed)
{
    uint16_t x = htons(dto->x_pos());
    uint16_t y = htons(dto->y_pos());

    skt->sendall(&(x), sizeof(x), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(y), sizeof(y), &was_closed);
    if (was_closed)
        return false;

    // printf("codigo : %u\n", code);
    return !was_closed;
}

bool ServerProtocol::enviarId(std::shared_ptr<ClienteId> id, bool &was_closed)
{
    if (not enviarCodigoDeElemento(id, was_closed))
        return false;

    uint8_t id_cliente = id->get_cliente_id();
    skt->sendall(&(id_cliente), sizeof(id_cliente), &was_closed);

    // printf("id enviado: %u\n", id_cliente);
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
            return false;
    }

    return true;
}

bool ServerProtocol::enviarViga(std::shared_ptr<Dto> dto, bool &was_closed)
{
    uint16_t ancho = htons(dto->return_ancho());
    uint16_t alto = htons(dto->return_alto());
    uint16_t angulo = htons(dto->return_angulo());

    if (not enviarPosicionDelElemento(dto, was_closed))
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
    uint8_t vida = g->get_vida();
    uint8_t color = g->get_color();
    uint8_t estado = g->get_estado();
    uint8_t arma = g->get_arma();
    uint8_t direccion = g->get_direccion();
    uint8_t angulo = g->get_angulo();

    skt->sendall(&(id), sizeof(id), &was_closed);
    if (was_closed)
        return false;

    if (not enviarPosicionDelElemento(g, was_closed))
        return false;

    skt->sendall(&(vida), sizeof(vida), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(color), sizeof(color), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(estado), sizeof(estado), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(arma), sizeof(arma), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(direccion), sizeof(direccion), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(angulo), sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    // printf("id:%u  x:%u  y:%u vida:%u color:%u\n", g->get_id(), g->x_pos(), g->y_pos(), g->get_vida(), g->get_color());
    // printf("estado: %u\n", g->get_estado());
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
    // printf("flag: %u",flag);

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

bool ServerProtocol::enviarGanador(std::shared_ptr<Dto> dto, bool &was_closed)
{
    if (not enviarCodigoDeElemento(dto, was_closed))
        return false;

    uint8_t id = dto->get_cliente_id();
    skt->sendall(&(id), sizeof(id), &was_closed);
    if (was_closed)
        return false;

    return true;
}

bool ServerProtocol::enviarGranada(std::shared_ptr<Proyectil> dto, bool &was_closed)
{
    if (not enviarCodigoDeElemento(dto, was_closed))
        return false;

    if (not enviarPosicionDelElemento(dto, was_closed))
        return false;

    uint8_t angulo = dto->get_angulo();
    skt->sendall(&(angulo), sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    uint8_t exploto = dto->get_exploto();
    skt->sendall(&(exploto), sizeof(exploto), &was_closed);
    if (was_closed)
        return false;

    uint8_t tiempo = dto->get_tiempo();
    skt->sendall(&(tiempo), sizeof(tiempo), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria enviada granada ---> x:%u y:%u angulo:%u exploto: %u tiempo: %u\n", dto->x_pos(), dto->y_pos(), angulo, exploto, tiempo);
    return true;
}

bool ServerProtocol::enviarTrayectoriaDeGranadaVerde(std::shared_ptr<GranadaVerde> g, bool &was_closed)
{
    return enviarGranada(g, was_closed);
}

bool ServerProtocol::enviarTrayectoriaDeGranadaBanana(std::shared_ptr<GranadaBanana> g, bool &was_closed)
{
    return enviarGranada(g, was_closed);
}

bool ServerProtocol::enviarTrayectoriaDeGranadaSanta(std::shared_ptr<GranadaSanta> g, bool &was_closed)
{
    return enviarGranada(g, was_closed);
}

bool ServerProtocol::enviarTrayectoriaDeDinamita(std::shared_ptr<Dinamita> g, bool &was_closed)
{
    if (not enviarCodigoDeElemento(g, was_closed))
        return false;

    if (not enviarPosicionDelElemento(g, was_closed))
        return false;

    uint8_t exploto = g->get_exploto();
    skt->sendall(&(exploto), sizeof(exploto), &was_closed);
    if (was_closed)
        return false;

    uint8_t tiempo = g->get_tiempo();
    skt->sendall(&(tiempo), sizeof(tiempo), &was_closed);
    if (was_closed)
        return false;
    // printf("Trayectoria ---> x:%u y:%u \n", g->x_pos(), g->y_pos());

    return true;
}

bool ServerProtocol::enviarTrayectoriaDeMisil(std::shared_ptr<Misil> g, bool &was_closed)
{
    if (not enviarCodigoDeElemento(g, was_closed))
        return false;

    uint8_t id = g->get_id();
    skt->sendall(&(id), sizeof(id), &was_closed);
    if (was_closed)
        return false;

    if (not enviarPosicionDelElemento(g, was_closed))
        return false;

    uint8_t exploto = g->get_exploto();
    skt->sendall(&(exploto), sizeof(exploto), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria enviada misil ---> id:%u x:%u y:%u \n", id, g->x_pos(), g->y_pos());

    return true;
}

bool ServerProtocol::enviarTrayectoriaDeFragmento(std::shared_ptr<Fragmento> f, bool &was_closed)
{
    if (not enviarCodigoDeElemento(f, was_closed))
        return false;

    uint8_t id = f->get_id();
    skt->sendall(&(id), sizeof(id), &was_closed);
    if (was_closed)
        return false;

    if (not enviarPosicionDelElemento(f, was_closed))
        return false;

    uint8_t angulo = f->get_angulo();
    skt->sendall(&(angulo), sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    uint8_t exploto = f->get_exploto();
    skt->sendall(&(exploto), sizeof(exploto), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria enviada fragmento ---> id:%u x:%u y:%u angulo:%u exploto: %u\n", id, f->x_pos(), f->y_pos(), angulo, exploto);

    return true;
}

bool ServerProtocol::enviarTrayectoriaDeBazuka(std::shared_ptr<Bazuka> b, bool &was_closed)
{
    if (not enviarCodigoDeElemento(b, was_closed))
        return false;

    uint8_t angulo = b->get_angulo();
    uint8_t direccion = b->get_direccion();
    uint8_t exploto = b->get_exploto();

    if (not enviarPosicionDelElemento(b, was_closed))
        return false;

    skt->sendall(&(angulo), sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(direccion), sizeof(direccion), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(exploto), sizeof(exploto), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria BAZUKA---> x:%u y:%u \n", b->x_pos(), b->y_pos());

    return true;
}

bool ServerProtocol::enviarTrayectoriaDeMortero(std::shared_ptr<Mortero> b, bool &was_closed)
{
    if (not enviarCodigoDeElemento(b, was_closed))
        return false;

    uint8_t angulo = b->get_angulo();
    uint8_t direccion = b->get_direccion();
    uint8_t exploto = b->get_exploto();

    if (not enviarPosicionDelElemento(b, was_closed))
        return false;

    skt->sendall(&(angulo), sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(direccion), sizeof(direccion), &was_closed);
    if (was_closed)
        return false;

    skt->sendall(&(exploto), sizeof(exploto), &was_closed);
    if (was_closed)
        return false;

    // printf("Trayectoria BAZUKA---> x:%u y:%u \n", b->x_pos(), b->y_pos());

    return true;
}

bool ServerProtocol::enviarProyectil(std::shared_ptr<Proyectil> p, bool &was_closed)
{
    uint8_t code = p->return_code(); // el codigo se encargan de enviarlo las funciones
    if (esGranada(code))
        return enviarGranada(p, was_closed);
    else if (code == BAZUKA_CODE)
        return enviarTrayectoriaDeBazuka(std::dynamic_pointer_cast<Bazuka>(p), was_closed);
    else if (code == MORTERO_CODE)
        return enviarTrayectoriaDeMortero(std::dynamic_pointer_cast<Mortero>(p), was_closed);
    else if (code == DINAMITA_CODE)
        return enviarTrayectoriaDeDinamita(std::dynamic_pointer_cast<Dinamita>(p), was_closed);
    else if (code == ATAQUE_AEREO_CODE)
        return enviarTrayectoriaDeMisil(std::dynamic_pointer_cast<Misil>(p), was_closed);
    else if (code == FRAGMENTO_CODE)
        return enviarTrayectoriaDeFragmento(std::dynamic_pointer_cast<Fragmento>(p), was_closed);

    return false;
}

bool ServerProtocol::enviarProyectiles(std::shared_ptr<Proyectiles> proyectiles, bool &was_closed)
{
    // std::cout << "entro a enviar proyectil\n";
    if (not enviarCodigoDeElemento(proyectiles, was_closed))
        return false;

    uint8_t cantidad = proyectiles->cantidad();

    skt->sendall(&(cantidad), sizeof(cantidad), &was_closed);
    if (was_closed)
        return false;

    for (int i = 0; i < cantidad; i++)
    {
        std::shared_ptr<Proyectil> p = proyectiles->popProyectil(i);
        if (not enviarProyectil(p, was_closed))
            return false;
    }

    // printf("Trayectoria BAZUKA---> x:%u y:%u \n", b->x_pos(), b->y_pos());

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ServerProtocol::esGranada(uint8_t code)
{
    return (code == GRANADA_BANANA_CODE || code == GRANADA_SANTA_CODE || code == GRANADA_VERDE_CODE || code == GRANADA_ROJA_CODE);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaque(uint8_t code, uint8_t id, bool &was_closed)
{
    if (code == BATEAR_CODE)
        return recibirAtaqueConBate(id, was_closed);
    else if (code == BAZUKA_CODE)
        return recibirAtaqueConBazuka(id, was_closed);
    else if (code == MORTERO_CODE)
        return recibirAtaqueConMortero(id, was_closed);
    else if (code == DINAMITA_CODE)
        return recibirAtaqueConDinamita(id, was_closed);
    else if (code == ATAQUE_AEREO_CODE)
        return recibirAtaqueAereo(id, was_closed);
    else if (esGranada(code))
        return recibirAtaqueConGranada(code, id, was_closed);

    return std::make_shared<DeadDto>();
}

std::shared_ptr<Dto> ServerProtocol::recibirPartidaSeleccionada(uint8_t id, bool &was_closed)
{
    uint8_t op;
    skt->recvall(&op, sizeof(op), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("opcion recibida: %u\n", op);
    return std::make_shared<ListaDePartidas>(id, op);
}

std::shared_ptr<Dto> ServerProtocol::recibirTeletransportacion(uint8_t id, bool &was_closed)
{
    uint16_t x;
    skt->recvall(&x, sizeof(x), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint16_t y;
    skt->recvall(&y, sizeof(y), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    x = ntohs(x);
    y = ntohs(y);

    // printf("x: %u y:%u\n", x, y);
    return std::make_shared<Teletransportar>(id, x, y);
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

bool ServerProtocol::recibirGranada(uint8_t &potencia, uint8_t &angulo, uint8_t &tiempo, bool &was_closed)
{
    uint8_t potencia_recibida;
    uint8_t angulo_recibido;
    uint8_t tiempo_recibido;

    skt->recvall(&potencia_recibida, sizeof(potencia_recibida), &was_closed);
    if (was_closed)
        return false;

    skt->recvall(&angulo_recibido, sizeof(angulo_recibido), &was_closed);
    if (was_closed)
        return false;

    skt->recvall(&tiempo_recibido, sizeof(tiempo_recibido), &was_closed);
    if (was_closed)
        return false;

    potencia = potencia_recibida;
    angulo = angulo_recibido;
    tiempo = tiempo_recibido;

    // printf("RECIBIR ---> angulo:%u pot: %u tiempo: %u\n", angulo, potencia, tiempo);

    return true;
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConGranada(uint8_t code, uint8_t id, bool &was_closed)
{
    uint8_t potencia;
    uint8_t angulo;
    uint8_t tiempo;

    if (not recibirGranada(potencia, angulo, tiempo, was_closed))
        return std::make_shared<DeadDto>();

    // printf("angulo recibido: %u\n", angulo);
    if (code == GRANADA_BANANA_CODE)
        return std::make_shared<GranadaBanana>(id, potencia, angulo, tiempo);
    else if (code == GRANADA_SANTA_CODE)
        return std::make_shared<GranadaSanta>(id, potencia, angulo, tiempo);
    else if (code == GRANADA_VERDE_CODE)
        return std::make_shared<GranadaVerde>(id, potencia, angulo, tiempo);
    else if (code == GRANADA_ROJA_CODE)
        return std::make_shared<GranadaRoja>(id, potencia, angulo, tiempo);

    return std::make_shared<DeadDto>();
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConDinamita(uint8_t id, bool &was_closed)
{
    uint8_t tiempo;
    skt->recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("angulo recibido: %u\n", angulo);
    return std::make_shared<Dinamita>(id, tiempo, false);
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
    return std::make_shared<Bazuka>(id, potencia, angulo, false);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueConMortero(uint8_t id, bool &was_closed)
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
    return std::make_shared<Mortero>(id, potencia, angulo, false);
}

std::shared_ptr<Dto> ServerProtocol::recibirParametrosDeLaPartida(bool &was_closed)
{
    uint8_t cantidad_de_jugadores;
    skt->recvall(&cantidad_de_jugadores, sizeof(cantidad_de_jugadores), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t mapa;
    skt->recvall(&mapa, sizeof(mapa), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("jugadores recibido: %u\n", cantidad_de_jugadores);
    return std::make_shared<NuevaPartida>(cantidad_de_jugadores, mapa);
}

std::shared_ptr<Dto> ServerProtocol::recibirSalto(uint8_t id, bool &was_closed)
{
    uint8_t direccion;
    skt->recvall(&direccion, sizeof(direccion), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("jugadores recibido: %u\n", cantidad_de_jugadores);
    return std::make_shared<Saltar>(id, direccion);
}

std::shared_ptr<Dto> ServerProtocol::recibirAtaqueAereo(uint8_t id, bool &was_closed)
{
    uint16_t x;
    skt->recvall(&x, sizeof(x), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint16_t y;
    skt->recvall(&y, sizeof(y), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    x = ntohs(x);
    y = ntohs(y);

    // printf("recibir pos ataque: %u %u %u\n", id, x, y);
    return std::make_shared<Misil>(id, x, y, false);
}

std::shared_ptr<Dto> ServerProtocol::recibirEquipadoDeArma(uint8_t id, bool &was_closed)
{
    uint8_t arma;
    skt->recvall(&arma, sizeof(arma), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("recibir pos ataque: %u\n", arma);
    return std::make_shared<EquiparArma>(id, arma);
}

std::shared_ptr<Dto> ServerProtocol::recibirCheat(uint8_t id, bool &was_closed)
{
    uint8_t cheat;
    skt->recvall(&cheat, sizeof(cheat), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("recibir pos ataque: %u %u %u\n", id, x, y);
    return std::make_shared<Cheat>(id, cheat);
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
    else if (code == FINALIZAR_CODE)
        return std::make_shared<Dto>(FINALIZAR_CODE, id);
    else if (code == SALTAR_CODE)
        return recibirSalto(id, was_closed);
    else if (code == NUEVA_PARTIDA_CODE)
        return recibirParametrosDeLaPartida(was_closed);
    else if (code == TELETRANSPORTAR_CODE)
        return recibirTeletransportacion(id, was_closed);
    else if (code == EQUIPAR_ARMA_CODE)
        return recibirEquipadoDeArma(id, was_closed);
    else if (code == CHEAT_CODE)
        return recibirCheat(id, was_closed);
    else
        return recibirAtaque(code, id, was_closed);

    return std::make_shared<DeadDto>();
}
