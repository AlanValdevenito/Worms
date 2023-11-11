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

    // printf("codigo:%u\n",code);

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
    else if (code == GRANADA_VERDE_CODE)
        return recibirTrayectoriaGranadaVerde(was_closed);
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

    // print

    return true;
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

    skt.recvall(&x, sizeof(x), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&y, sizeof(y), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();
    // recibirPosicion(x, y, was_closed);

    skt.recvall(&ancho, sizeof(ancho), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&alto, sizeof(alto), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    x = ntohs(x);
    y = ntohs(y);
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
<<<<<<< HEAD
=======
        return std::make_shared<DeadDto>();

    uint8_t flag;
    skt.recvall(&flag, sizeof(flag), &was_closed);
    if (was_closed)
>>>>>>> granada_verde
        return std::make_shared<DeadDto>();

    // printf("cant: %u\n",cant);
    //printf("flag: %u\n",flag);

    std::vector<std::shared_ptr<Gusano>> lista;
    for (int i = 0; i < cant; i++)
    {
        std::shared_ptr<Gusano> g = std::dynamic_pointer_cast<Gusano>(recibirGusano(was_closed));

        // printf("gusano %d)  id:%u  x:%u  y:%u \n", i, g->get_id(), g->x_pos(), g->y_pos());

        lista.push_back(g);
    }
    std::shared_ptr<Gusanos> gusanos = std::make_shared<Gusanos>(lista);
    gusanos->set_gusano_de_turno(turno);
<<<<<<< HEAD
=======
    gusanos->set_flag_proyectil(flag);
>>>>>>> granada_verde
    return gusanos;
}

std::shared_ptr<Dto> ClientProtocol::recibirGusano(bool &was_closed)
{
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint8_t vida;
    uint8_t color;

    skt.recvall(&id, sizeof(id), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&x, sizeof(x), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&y, sizeof(y), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&vida, sizeof(vida), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&color, sizeof(color), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    x = ntohs(x);
    y = ntohs(y);

    // printf("Cliente ---> id:%u  x:%u y:%u  vida:%u color:%u\n", id, x, y, vida, color);

    return std::make_shared<Gusano>(id, x, y, vida, color);
}

std::shared_ptr<Dto> ClientProtocol::recibirTrayectoriaGranadaVerde(bool &was_closed)
{
    uint16_t x;
    uint16_t y;

    skt.recvall(&x, sizeof(x), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    skt.recvall(&y, sizeof(y), &was_closed);
    if (was_closed)
        return std::make_shared<DeadDto>();

    x = ntohs(x);
    y = ntohs(y);

    // printf("Trayectoria ---> x:%u y:%u \n", x, y);

    return std::make_shared<GranadaVerde>(x, y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

bool ClientProtocol::moverADerecha(std::shared_ptr<MoverADerecha> m, bool &was_closed)
{
    return enviarIdDelClienteYCodigoDeAccion(m, was_closed);
}

bool ClientProtocol::moverAIzquierda(std::shared_ptr<MoverAIzquierda> m, bool &was_closed)
{
    return enviarIdDelClienteYCodigoDeAccion(m, was_closed);
}

bool ClientProtocol::saltar(std::shared_ptr<Dto> s, bool &was_closed)
{
    return enviarIdDelClienteYCodigoDeAccion(s, was_closed);
}

bool ClientProtocol::enviarNuevaPartida(std::shared_ptr<NuevaPartida> n, bool &was_closed)
{
    bool se_envio = enviarIdDelClienteYCodigoDeAccion(n, was_closed);
    if (!se_envio)
        return se_envio;

    uint8_t cantidad_de_jugadores = n->get_cantidad_de_jugadores();
    // printf("jugadores: %u\n", cantidad_de_jugadores);
    skt.sendall(&cantidad_de_jugadores, sizeof(cantidad_de_jugadores), &was_closed);

    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarSeleccion(std::shared_ptr<ListaDePartidas> l, bool &was_closed)
{

    bool se_envio = enviarIdDelClienteYCodigoDeAccion(l, was_closed);
    if (!se_envio)
        return se_envio;

    uint8_t opcion = l->seleccionada;
    // printf("enviar opcion: %u\n", opcion);
    skt.sendall(&opcion, sizeof(opcion), &was_closed);
    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarFinDePartida(std::shared_ptr<Dto> dto, bool &was_closed)
{
    return enviarIdDelClienteYCodigoDeAccion(dto, was_closed);
}

bool ClientProtocol::enviarAtaqueConBate(std::shared_ptr<Batear> b, bool &was_closed)
{
    bool se_envio = enviarIdDelClienteYCodigoDeAccion(b, was_closed);
    if (!se_envio)
        return se_envio;

    // printf("enviar: %u\n", a);
    uint8_t angulo = b->get_angulo();
    skt.sendall(&angulo, sizeof(angulo), &was_closed);

    if (was_closed)
        return false;

    return true;
}

bool ClientProtocol::enviarAtaqueConGranadaVerde(std::shared_ptr<GranadaVerde> g, bool &was_closed)
{
    bool se_envio = enviarIdDelClienteYCodigoDeAccion(g, was_closed);
    if (!se_envio)
        return se_envio;

    uint8_t potencia = g->get_potencia();
    skt.sendall(&potencia, sizeof(potencia), &was_closed);
    if (was_closed)
        return false;

    uint8_t angulo = g->get_angulo();
    skt.sendall(&angulo, sizeof(angulo), &was_closed);
    if (was_closed)
        return false;

    uint8_t tiempo = g->get_tiempo();
    skt.sendall(&tiempo, sizeof(tiempo), &was_closed);
    if (was_closed)
        return false;

    return true;
}
