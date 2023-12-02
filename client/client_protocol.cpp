#include "client_protocol.h"

ClientProtocol::ClientProtocol(SocketInterface &skt) : skt(skt) {}

ClientProtocol::~ClientProtocol() {}

// ACA SE HACE LA SEPARACION MEDIANTE EL CODIGO QUE RECIBO PRIMERO
std::shared_ptr<Dto> ClientProtocol::receive(bool &was_closed)
{
    uint8_t code;
    skt.recvall(&code, sizeof(code), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("codigo:%u\n", code);

    if (code == VIGA_CODE)
        return recibirVigas(was_closed);
    else if (code == GUSANO_CODE)
        return recibirGusano(was_closed);
    else if (code == GUSANOS_CODE)
        return recibirGusanos(was_closed);
    else if (code == LISTA_DE_PARTIDAS_CODE)
        return recibirPartidas(was_closed);
    else if (code == CLIENTE_ID_CODE)
        return recibirId(was_closed);
    else if (code == INICIAR_PARIDA)
        return std::make_shared<Dto>(INICIAR_PARIDA);
    else if (code == FINALIZAR_CODE)
        return std::make_shared<DeadDto>();
    else if (code == PROYECTILES_CODE)
        return recibirProyectiles(was_closed);
    else if (code == GANADOR_CODE)
        return recibirGanador(was_closed);
    else
        std::cerr << "Codigo recibido sin identificar\n";

    return std::make_shared<DeadDto>();
}

std::shared_ptr<Dto> ClientProtocol::recibirId(bool &was_closed)
{
    uint8_t id;
    skt.recvall(&id, sizeof(id), &was_closed);

    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("id recibido: %u\n", id);
    return std::make_shared<ClienteId>(id);
}

std::shared_ptr<Dto> ClientProtocol::recibirPartidas(bool &was_closed)
{

    uint8_t cant;
    skt.recvall(&cant, sizeof(cant), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t op;
    std::shared_ptr<ListaDePartidas> l = std::make_shared<ListaDePartidas>();

    for (int i = 0; i < cant; i++)
    {
        skt.recvall(&op, sizeof(op), &was_closed);
        if (was_closed)
            return std::make_shared<DeadDto>();
        l->addOption(op);
    }

    return l;
}

uint8_t ClientProtocol::cantidadARecibir(bool &was_closed)
{
    uint8_t cant;
    skt.recvall(&cant, sizeof(cant), &was_closed);
    if (was_closed)
        return -1;

    // printf("cant: %u\n", cant);
    return cant;
}

bool ClientProtocol::recibirPosicion(uint16_t &x, uint16_t &y, bool &was_closed)
{
    uint16_t posicion_x;
    uint16_t posicion_y;
    skt.recvall(&posicion_x, sizeof(posicion_x), &was_closed);
    if (was_closed)
        return false;

    skt.recvall(&posicion_y, sizeof(posicion_y), &was_closed);
    if (was_closed)
        return false;

    x = ntohs(posicion_x);
    y = ntohs(posicion_y);

    // printf("%u %u\n", x, y);
    // printf("%u %u\n", posicion_x, posicion_y);

    return true;
}

std::shared_ptr<Dto> ClientProtocol::recibirGanador(bool &was_closed)
{
    uint8_t id;
    skt.recvall(&id, sizeof(id), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    return std::make_shared<Ganador>(id);
}

std::shared_ptr<Dto> ClientProtocol::recibirVigas(bool &was_closed)
{
    uint8_t cant = cantidadARecibir(was_closed);
    if (cant < 0)
        return std::make_shared<DeadDto>();

    std::vector<std::shared_ptr<Viga>> vs;
    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Viga> v = std::dynamic_pointer_cast<Viga>(recibirViga(was_closed));
        vs.push_back(v);
    }
    return std::make_shared<Vigas>(vs);
}

std::shared_ptr<Dto> ClientProtocol::recibirViga(bool &was_closed)
{
    uint16_t x;
    uint16_t y;
    uint16_t ancho;
    uint16_t alto;
    uint16_t angulo;

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&ancho, sizeof(ancho), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&alto, sizeof(alto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    ancho = ntohs(ancho);
    alto = ntohs(alto);
    angulo = ntohs(angulo);

    // printf("Cliente ---> x:%u  y:%u ancho:%u  alto:%u  angulo:%u  \n", x, y, ancho, alto, angulo);

    return std::make_shared<Viga>(x, y, ancho, alto, angulo);
}

std::shared_ptr<Dto> ClientProtocol::recibirGusanos(bool &was_closed)
{
    uint8_t cant = cantidadARecibir(was_closed);
    if (cant < 0)
        return std::make_shared<DeadDto>();

    uint8_t turno;
    skt.recvall(&turno, sizeof(turno), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t flag;
    skt.recvall(&flag, sizeof(flag), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("flag: %u turno:%u cant: %u\n",flag, turno, cant);

    std::vector<std::shared_ptr<Gusano>> lista;
    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Gusano> g = std::dynamic_pointer_cast<Gusano>(recibirGusano(was_closed));
        lista.push_back(g);
    }
    std::shared_ptr<Gusanos> gusanos = std::make_shared<Gusanos>(lista);
    gusanos->set_gusano_de_turno(turno);
    gusanos->set_flag_proyectil(flag);
    return gusanos;
}

std::shared_ptr<Dto> ClientProtocol::recibirGusano(bool &was_closed)
{
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint8_t vida;
    uint8_t color;
    uint8_t estado;
    uint8_t arma;
    uint8_t direccion;
    uint8_t angulo;

    skt.recvall(&id, sizeof(id), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&vida, sizeof(vida), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&color, sizeof(color), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&estado, sizeof(estado), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&arma, sizeof(arma), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&direccion, sizeof(direccion), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Cliente ---> id:%u   vida:%u color:%u estado:%u arma:%u dir: %u\n", id, vida, color, estado, arma, direccion);
    // printf("id:%u\n", id);

    return std::make_shared<Gusano>(id, x, y, vida, color, estado, arma, direccion, angulo);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaGranadaVerde(bool &was_closed)
{

    uint16_t x;
    uint16_t y;
    uint8_t angulo;

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t exploto;
    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t tiempo;
    skt.recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Trayectoria ---> x:%u y:%u exploto: %u tiempo: %u\n", x, y, exploto, tiempo);

    return std::make_shared<GranadaVerde>(x, y, angulo, exploto, tiempo);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaGranadaBanana(bool &was_closed)
{
    uint16_t x;
    uint16_t y;
    uint8_t angulo;

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();
    // printf("Trayectoria ---> x:%u y:%u \n", x, y);

    uint8_t exploto;
    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t tiempo;
    skt.recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Trayectoria ---> x:%u y:%u exploto: %u tiempo: %u\n", x, y, exploto, tiempo);
    return std::make_shared<GranadaBanana>(x, y, angulo, exploto, tiempo);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaGranadaSanta(bool &was_closed)
{
    uint16_t x;
    uint16_t y;
    uint8_t angulo;

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();
    // printf("Trayectoria ---> x:%u y:%u \n", x, y);

    uint8_t exploto;
    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t tiempo;
    skt.recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Trayectoria ---> x:%u y:%u exploto: %u tiempo: %u\n", x, y, exploto, tiempo);
    return std::make_shared<GranadaSanta>(x, y, angulo, exploto, tiempo);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaGranadaRoja(bool &was_closed)
{
    uint16_t x;
    uint16_t y;
    uint8_t angulo;

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t exploto;
    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t tiempo;
    skt.recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("GRANADA ROJA---> x:%u y:%u angulo:%u exploto: %u tiempo: %u\n", x, y, angulo, exploto, tiempo);
    return std::make_shared<GranadaRoja>(x, y, angulo, exploto, tiempo);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaDinamita(bool &was_closed)
{
    uint16_t x;
    uint16_t y;

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    uint8_t exploto;
    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t tiempo;
    skt.recvall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Trayectoria ---> x:%u y:%u tiempo: %u\n", x, y, tiempo);

    return std::make_shared<Dinamita>(x, y, exploto, tiempo);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaBazuka(bool &was_closed)
{
    uint16_t x;
    uint16_t y;
    uint8_t angulo;
    uint8_t direccion;

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&direccion, sizeof(direccion), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t exploto;
    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Trayectoria recibida---> x:%u y:%u angulo:%u\n", x, y,angulo);

    return std::make_shared<Bazuka>(x, y, angulo, direccion, exploto);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaMortero(bool &was_closed)
{
    uint16_t x;
    uint16_t y;
    uint8_t angulo;
    uint8_t direccion;

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&direccion, sizeof(direccion), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    uint8_t exploto;
    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Trayectoria recibida---> x:%u y:%u angulo:%u\n", x, y,angulo);

    return std::make_shared<Mortero>(x, y, angulo, direccion, exploto);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaMisil(bool &was_closed)
{
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint8_t exploto;

    skt.recvall(&id, sizeof(id), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Trayectoria misil---> id:%u x:%u y:%u \n", id,x, y);

    return std::make_shared<Misil>(id, x, y, exploto);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaFragmento(bool &was_closed)
{
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint8_t angulo;
    uint8_t exploto;

    skt.recvall(&id, sizeof(id), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    if (not recibirPosicion(x, y, was_closed))
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&exploto, sizeof(exploto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("Trayectoria fragmento---> id:%u x:%u y:%u angulo: %u exploto: %u\n", id,x, y, angulo,exploto);

    return std::make_shared<Fragmento>(id, x, y, angulo, exploto);
}

std::shared_ptr<Dto> ClientProtocol::recibirProyectil(bool &was_closed)
{

    uint8_t code;
    skt.recvall(&code, sizeof(code), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    // printf("codigo:%u\n", code);
    if (code == GRANADA_VERDE_CODE)
        return recibirTrayectoriaGranadaVerde(was_closed);
    else if (code == GRANADA_BANANA_CODE)
        return recibirTrayectoriaGranadaBanana(was_closed);
    else if (code == GRANADA_SANTA_CODE)
        return recibirTrayectoriaGranadaSanta(was_closed);
    else if (code == GRANADA_ROJA_CODE)
        return recibirTrayectoriaGranadaRoja(was_closed);
    else if (code == DINAMITA_CODE)
        return recibirTrayectoriaDinamita(was_closed);
    else if (code == BAZUKA_CODE)
        return recibirTrayectoriaBazuka(was_closed);
    else if (code == ATAQUE_AEREO_CODE)
        return recibirTrayectoriaMisil(was_closed);
    else if (code == MORTERO_CODE)
        return recibirTrayectoriaMortero(was_closed);
    else if (code == FRAGMENTO_CODE)
        return recibirTrayectoriaFragmento(was_closed);

    return std::make_shared<DeadDto>();
}

std::shared_ptr<Dto> ClientProtocol::recibirProyectiles(bool &was_closed)
{
    uint8_t cant = cantidadARecibir(was_closed);
    if (cant < 0)
        return std::make_shared<DeadDto>();

    // printf("cantidad de proyectiles: %u\n", cant);

    std::vector<std::shared_ptr<Proyectil>> ps;
    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Proyectil> p = std::dynamic_pointer_cast<Proyectil>(recibirProyectil(was_closed));
        if (not p->is_alive())
            return std::make_shared<DeadDto>();
        ps.push_back(p);
    }
    return std::make_shared<Proyectiles>(ps);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ClientProtocol::enviarMovimiento(std::shared_ptr<Dto> dto, bool &was_closed)
{

    if (dto->return_code() == MOVER_A_DERECHA_CODE)
        return moverADerecha(std::dynamic_pointer_cast<MoverADerecha>(dto), was_closed);
    else if (dto->return_code() == MOVER_A_IZQUIERDA_CODE)
        return moverAIzquierda(std::dynamic_pointer_cast<MoverAIzquierda>(dto), was_closed);
    else if (dto->return_code() == SALTAR_CODE)
        return saltar(std::dynamic_pointer_cast<Saltar>(dto), was_closed);
    else if (dto->return_code() == TELETRANSPORTAR_CODE)
        return enviarTeletrasnportacion(std::dynamic_pointer_cast<Teletransportar>(dto), was_closed);
    else
        return false;
}

bool ClientProtocol::enviarAtaque(std::shared_ptr<Dto> dto, bool &was_closed)
{

    if (dto->return_code() == BATEAR_CODE)
        return enviarAtaqueConBate(std::dynamic_pointer_cast<Batear>(dto), was_closed);
    else if (dto->return_code() == GRANADA_VERDE_CODE)
        return enviarAtaqueConGranadaVerde(std::dynamic_pointer_cast<GranadaVerde>(dto), was_closed);
    else if (dto->return_code() == BAZUKA_CODE)
        return enviarAtaqueConBazuka(std::dynamic_pointer_cast<Bazuka>(dto), was_closed);
    else if (dto->return_code() == GRANADA_BANANA_CODE)
        return enviarAtaqueConGranadaBanana(std::dynamic_pointer_cast<GranadaBanana>(dto), was_closed);
    else if (dto->return_code() == GRANADA_SANTA_CODE)
        return enviarAtaqueConGranadaSanta(std::dynamic_pointer_cast<GranadaSanta>(dto), was_closed);
    else if (dto->return_code() == GRANADA_ROJA_CODE)
        return enviarAtaqueConGranadaRoja(std::dynamic_pointer_cast<GranadaRoja>(dto), was_closed);
    else if (dto->return_code() == DINAMITA_CODE)
        return enviarAtaqueConDinamita(std::dynamic_pointer_cast<Dinamita>(dto), was_closed);
    else if (dto->return_code() == ATAQUE_AEREO_CODE)
        return enviarAtaqueaereo(std::dynamic_pointer_cast<Misil>(dto), was_closed);
    else if (dto->return_code() == MORTERO_CODE)
        return enviarAtaqueConMortero(std::dynamic_pointer_cast<Mortero>(dto), was_closed);
    else
        return false;
}

bool ClientProtocol::enviarIdDelClienteYCodigoDeAccion(std::shared_ptr<Dto> dto, bool &was_closed)
{
    // printf("enviar: %u\n", a);

    uint8_t id_cliente = dto->get_cliente_id();
    skt.sendall(&id_cliente, sizeof(id_cliente), &was_closed);
    if (was_closed)
        return false;

    uint8_t code = dto->return_code();
    skt.sendall(&code, sizeof(code), &was_closed);
    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarAnguloYPotenciaDeProyectil(std::shared_ptr<Proyectil> dto, bool &was_closed)
{
    // printf("enviar: %u\n", a);

    uint8_t potencia = dto->get_potencia();
    skt.sendall(&potencia, sizeof(potencia), &was_closed);
    if (was_closed)
        return false;

    uint8_t angulo = dto->get_angulo();
    skt.sendall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::moverADerecha(std::shared_ptr<MoverADerecha> m, bool &was_closed)
{
    return enviarIdDelClienteYCodigoDeAccion(m, was_closed);
}

bool ClientProtocol::moverAIzquierda(std::shared_ptr<MoverAIzquierda> m, bool &was_closed)
{
    return enviarIdDelClienteYCodigoDeAccion(m, was_closed);
}

bool ClientProtocol::saltar(std::shared_ptr<Saltar> s, bool &was_closed)
{
    if (not enviarIdDelClienteYCodigoDeAccion(s, was_closed))
        return false;

    uint8_t direccion = s->get_direccion();
    skt.sendall(&direccion, sizeof(direccion), &was_closed);

    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarNuevaPartida(std::shared_ptr<NuevaPartida> n, bool &was_closed)
{
    if (not enviarIdDelClienteYCodigoDeAccion(n, was_closed))
        return false;

    uint8_t cantidad_de_jugadores = n->get_cantidad_de_jugadores();
    skt.sendall(&cantidad_de_jugadores, sizeof(cantidad_de_jugadores), &was_closed);

    uint8_t mapa = n->get_mapa();
    skt.sendall(&mapa, sizeof(mapa), &was_closed);
    // printf("jugadores: %u\n", cantidad_de_jugadores);

    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarSeleccion(std::shared_ptr<ListaDePartidas> l, bool &was_closed)
{

    if (not enviarIdDelClienteYCodigoDeAccion(l, was_closed))
        return false;

    uint8_t opcion = l->seleccionada;
    skt.sendall(&opcion, sizeof(opcion), &was_closed);
    if (was_closed)
        return false;

    // printf("enviar opcion: %u\n", opcion);
    return true;
}

bool ClientProtocol::enviarFinDePartida(std::shared_ptr<Dto> dto, bool &was_closed)
{
    return enviarIdDelClienteYCodigoDeAccion(dto, was_closed);
}

bool ClientProtocol::enviarAtaqueConBate(std::shared_ptr<Batear> b, bool &was_closed)
{
    if (not enviarIdDelClienteYCodigoDeAccion(b, was_closed))
        return false;

    // printf("enviar: %u\n", a);
    uint8_t angulo = b->get_angulo();
    skt.sendall(&angulo, sizeof(angulo), &was_closed);

    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarAtaqueConBazuka(std::shared_ptr<Bazuka> g, bool &was_closed)
{
    if (not enviarIdDelClienteYCodigoDeAccion(g, was_closed))
        return false;

    return enviarAnguloYPotenciaDeProyectil(g, was_closed);
}

bool ClientProtocol::enviarAtaqueConMortero(std::shared_ptr<Mortero> g, bool &was_closed)
{
    if (not enviarIdDelClienteYCodigoDeAccion(g, was_closed))
        return false;

    return enviarAnguloYPotenciaDeProyectil(g, was_closed);
}

bool ClientProtocol::enviarAtaqueConGranada(std::shared_ptr<Proyectil> g, bool &was_closed)
{

    if (not enviarIdDelClienteYCodigoDeAccion(g, was_closed))
        return false;

    if (not enviarAnguloYPotenciaDeProyectil(g, was_closed))
        return false;

    uint8_t tiempo = g->get_tiempo();
    skt.sendall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return false;

    // printf("ENVIAAAAAAAAAAAAAAAAAAR ------------_> angulo :%u pot: %u tiemp: %u\n", g->get_angulo(), g->get_potencia(), g->get_tiempo());

    return true;
}

bool ClientProtocol::enviarAtaqueConGranadaVerde(std::shared_ptr<GranadaVerde> g, bool &was_closed)
{
    return enviarAtaqueConGranada(g, was_closed);
}

bool ClientProtocol::enviarAtaqueConGranadaBanana(std::shared_ptr<GranadaBanana> g, bool &was_closed)
{
    return enviarAtaqueConGranada(g, was_closed);
}

bool ClientProtocol::enviarAtaqueConGranadaSanta(std::shared_ptr<GranadaSanta> g, bool &was_closed)
{
    return enviarAtaqueConGranada(g, was_closed);
}

bool ClientProtocol::enviarAtaqueConGranadaRoja(std::shared_ptr<GranadaRoja> g, bool &was_closed)
{
    return enviarAtaqueConGranada(g, was_closed);
}

bool ClientProtocol::enviarAtaqueConDinamita(std::shared_ptr<Dinamita> g, bool &was_closed)
{
    if (not enviarIdDelClienteYCodigoDeAccion(g, was_closed))
        return false;

    uint8_t tiempo = g->get_tiempo();
    skt.sendall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarTeletrasnportacion(std::shared_ptr<Teletransportar> t, bool &was_closed)
{
    if (not enviarIdDelClienteYCodigoDeAccion(t, was_closed))
        return false;

    uint16_t x = htons(t->x_pos());
    skt.sendall(&x, sizeof(x), &was_closed);
    if (was_closed)
        return false;

    uint16_t y = htons(t->y_pos());
    skt.sendall(&y, sizeof(y), &was_closed);
    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarAtaqueaereo(std::shared_ptr<Misil> t, bool &was_closed)
{

    if (not enviarIdDelClienteYCodigoDeAccion(t, was_closed))
        return false;

    uint16_t x = htons(t->x_pos());
    skt.sendall(&x, sizeof(x), &was_closed);
    if (was_closed)
        return false;

    uint16_t y = htons(t->y_pos());
    skt.sendall(&y, sizeof(y), &was_closed);
    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarEquipadoDeArma(std::shared_ptr<EquiparArma> e, bool &was_closed)
{

    if (not enviarIdDelClienteYCodigoDeAccion(e, was_closed))
        return false;

    uint8_t arma = e->get_arma();
    // printf("Envio ---> arma:%u\n", arma);
    skt.sendall(&arma, sizeof(arma), &was_closed);
    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarCheat(std::shared_ptr<Cheat> c, bool &was_closed)
{

    if (not enviarIdDelClienteYCodigoDeAccion(c, was_closed))
        return false;

    uint8_t cheat = c->get_cheat();
    // printf("Envio ---> cheat:%u\n", cheat);
    skt.sendall(&cheat, sizeof(cheat), &was_closed);
    if (was_closed)
        return false;

    return true;
}
