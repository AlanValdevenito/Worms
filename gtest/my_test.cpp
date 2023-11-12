#include <gtest/gtest.h>
#include "socket_mock.h"
#include "client.h"
#include "client_protocol.h"
#include "server_protocol.h"
#include "constantes.h"
#include "mover.h"

void printCliente()
{
    std::cout << "**********************************************************************************************************************\n";
    std::cout << "*                                   PRUEBAS PROTOCOLO CLIENTE                                                        *\n";
    std::cout << "**********************************************************************************************************************\n";
}

TEST(PROTOCOLOCLIENTE__ENVIO, __Mover_a_Derecha)
{
    // printCliente();
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 1;
    std::shared_ptr<MoverADerecha> mov = std::make_shared<MoverADerecha>(id);

    cp.moverADerecha(mov, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);

    // printf("%u %u\n", id_recibido, codigo_recibido);

    ASSERT_TRUE(id_recibido == id && codigo_recibido == MOVER_A_DERECHA_CODE);
}

TEST(PROTOCOLOCLIENTE__ENVIO, __Mover_a_Izquierda)
{

    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 1;
    std::shared_ptr<MoverAIzquierda> mov = std::make_shared<MoverAIzquierda>(id);

    cp.moverAIzquierda(mov, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);

    // printf("%u %u\n", id_recibido, codigo_recibido);

    ASSERT_TRUE(id_recibido == id && codigo_recibido == MOVER_A_IZQUIERDA_CODE);
}

TEST(PROTOCOLOCLIENTE__ENVIO, __Seleccion_de_partida)
{

    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 1;
    uint8_t seleccion = 2;
    std::shared_ptr<ListaDePartidas> selec = std::make_shared<ListaDePartidas>(id, seleccion);

    cp.enviarSeleccion(selec, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    uint8_t seleccion_recibida;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);
    skt.recvall(&seleccion_recibida, sizeof(seleccion_recibida), &was_closed);

    // printf("%u %u %u\n", id_recibido, codigo_recibido, seleccion_recibida);

    ASSERT_TRUE(id_recibido == id && codigo_recibido == LISTA_DE_PARTIDAS_CODE && seleccion_recibida == seleccion);
}

TEST(PROTOCOLOCLIENTE__ENVIO, __Ataque_con_bate)
{

    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 1;
    uint8_t angulo = 42;
    std::shared_ptr<Batear> b = std::make_shared<Batear>(id, angulo);

    cp.enviarAtaqueConBate(b, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    uint8_t angulo_recibido;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);
    skt.recvall(&angulo_recibido, sizeof(angulo_recibido), &was_closed);

    // printf("%u %u %u\n", id_recibido, codigo_recibido, angulo_recibido);

    ASSERT_TRUE(id_recibido == id && codigo_recibido == BATEAR_CODE && angulo_recibido == angulo);
}

TEST(PROTOCOLOCLIENTE__ENVIO, __Fin_de_partida)
{

    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 1;
    std::shared_ptr<Dto> fin = std::make_shared<Dto>(FINALIZAR_CODE, id);

    cp.enviarFinDePartida(fin, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);

    // printf("%u %u\n", id_recibido, codigo_recibido);

    ASSERT_TRUE(id_recibido == id && codigo_recibido == FINALIZAR_CODE);
}

TEST(PROTOCOLOCLIENTE__ENVIO, __Salto)
{

    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 1;
    std::shared_ptr<Saltar> saltar = std::make_shared<Saltar>(id);

    cp.saltar(saltar, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);

    // printf("%u %u\n", id_recibido, codigo_recibido);

    ASSERT_TRUE(id_recibido == id && codigo_recibido == SALTAR_CODE);
}

TEST(PROTOCOLOCLIENTE__ENVIO, __Peticion_de_nueva_partida)
{

    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t cantidad_de_jugadores = 4;
    std::shared_ptr<NuevaPartida> nueva_partida = std::make_shared<NuevaPartida>(cantidad_de_jugadores);

    cp.enviarNuevaPartida(nueva_partida, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    uint8_t cantidad_recibida;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);
    skt.recvall(&cantidad_recibida, sizeof(cantidad_recibida), &was_closed);

    // printf("%u %u\n", id_recibido, codigo_recibido);

    ASSERT_TRUE(id_recibido == 0 && codigo_recibido == NUEVA_PARTIDA_CODE && cantidad_recibida == cantidad_de_jugadores);
}

TEST(PROTOCOLOCLIENTE__ENVIO, __GranadaVerde)
{

    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 2;
    uint8_t potencia = 20;
    uint8_t angulo = 28;
    uint8_t tiempo = 5;
    std::shared_ptr<GranadaVerde> g = std::make_shared<GranadaVerde>(id, potencia, angulo, tiempo);

    cp.enviarAtaqueConGranadaVerde(g, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    uint8_t potencia_recibida;
    uint8_t angulo_recibido;
    uint8_t tiempo_recibido;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);
    skt.recvall(&potencia_recibida, sizeof(potencia_recibida), &was_closed);
    skt.recvall(&angulo_recibido, sizeof(angulo_recibido), &was_closed);
    skt.recvall(&tiempo_recibido, sizeof(tiempo_recibido), &was_closed);

    // printf("%u %u\n", id_recibido, codigo_recibido);

    ASSERT_TRUE(id_recibido == id);
    ASSERT_TRUE(codigo_recibido == GRANADA_VERDE_CODE);
    ASSERT_TRUE(potencia_recibida == potencia);
    ASSERT_TRUE(angulo_recibido == angulo);
    ASSERT_TRUE(tiempo_recibido == tiempo);
}

TEST(PROTOCOLOCLIENTE__ENVIO, __Bazooka)
{

    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 2;
    uint8_t potencia = 20;
    uint8_t angulo = 28;
    std::shared_ptr<Bazuka> g = std::make_shared<Bazuka>(id, potencia, angulo);

    cp.enviarAtaqueConBazuka(g, was_closed);

    uint8_t id_recibido;
    uint8_t codigo_recibido;
    uint8_t potencia_recibida;
    uint8_t angulo_recibido;
    skt.recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt.recvall(&codigo_recibido, sizeof(codigo_recibido), &was_closed);
    skt.recvall(&potencia_recibida, sizeof(potencia_recibida), &was_closed);
    skt.recvall(&angulo_recibido, sizeof(angulo_recibido), &was_closed);

    // printf("%u %u\n", id_recibido, codigo_recibido);

    ASSERT_TRUE(id_recibido == id);
    ASSERT_TRUE(codigo_recibido == BAZUKA_CODE);
    ASSERT_TRUE(potencia_recibida == potencia);
    ASSERT_TRUE(angulo_recibido == angulo);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(PROTOCOLOCLIENTE__RECIBIR, __ID_de_cliente)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;

    skt.sendall(&CLIENTE_ID_CODE, sizeof(CLIENTE_ID_CODE), &was_closed);
    uint8_t id = 9;
    skt.sendall(&id, sizeof(id), &was_closed);

    std::shared_ptr<Dto> rta = cp.receive(was_closed);

    // printf("%u \n", rta->get_cliente_id());

    ASSERT_TRUE(rta->get_cliente_id() == id);
}

TEST(PROTOCOLOCLIENTE__RECIBIR, __Lista_de_Partidas)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;

    uint8_t opcion1 = 1;
    uint8_t opcion2 = 6;
    uint8_t opcion3 = 2;
    std::list<uint8_t> lista_de_partidas;
    lista_de_partidas.push_back(opcion1);
    lista_de_partidas.push_back(opcion2);
    lista_de_partidas.push_back(opcion3);

    skt.sendall(&LISTA_DE_PARTIDAS_CODE, sizeof(LISTA_DE_PARTIDAS_CODE), &was_closed);
    uint8_t cant = lista_de_partidas.size();
    skt.sendall(&cant, sizeof(cant), &was_closed);

    for (uint8_t op : lista_de_partidas)
        skt.sendall(&op, sizeof(op), &was_closed);

    std::shared_ptr<ListaDePartidas> rta = std::dynamic_pointer_cast<ListaDePartidas>(cp.receive(was_closed));

    std::list<uint8_t> lista = rta->return_list();
    int sz = lista.size();

    // los optengo del ultimo insertado al primero
    uint8_t o3 = lista.back();
    lista.pop_back();
    uint8_t o2 = lista.back();
    lista.pop_back();
    uint8_t o1 = lista.back();
    lista.pop_back();

    // printf("%u %u %u %u \n", sz, o1, o2, o3);

    ASSERT_TRUE(sz == cant && o1 == opcion1 && o2 == opcion2 && o3 == opcion3);
}

void enviar_viga_con_parametros(SocketMock &skt, uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto, uint16_t angulo)
{
    bool was_closed = false;

    uint16_t x_a_enviar = htons(x);
    uint16_t y_a_enviar = htons(y);
    uint16_t ancho_a_enviar = htons(ancho);
    uint16_t alto_a_enviar = htons(alto);
    uint16_t angulo_a_enviar = htons(angulo);

    skt.sendall(&x_a_enviar, sizeof(x_a_enviar), &was_closed);
    skt.sendall(&y_a_enviar, sizeof(y_a_enviar), &was_closed);
    skt.sendall(&ancho_a_enviar, sizeof(ancho_a_enviar), &was_closed);
    skt.sendall(&alto_a_enviar, sizeof(alto_a_enviar), &was_closed);
    skt.sendall(&angulo_a_enviar, sizeof(angulo_a_enviar), &was_closed);
}

TEST(PROTOCOLOCLIENTE__RECIBIR, __Viga)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint16_t x = 20;
    uint16_t y = 10;
    uint16_t ancho = 10;
    uint16_t alto = 10;
    uint16_t angulo = 45;

    skt.sendall(&VIGA_CODE, sizeof(VIGA_CODE), &was_closed);
    uint8_t cant = 1; // hago como que le envie una lista con una sola viga
    skt.sendall(&cant, sizeof(cant), &was_closed);

    enviar_viga_con_parametros(std::ref(skt), x, y, ancho, alto, angulo);

    std::shared_ptr<Vigas> rta = std::dynamic_pointer_cast<Vigas>(cp.receive(was_closed));
    std::shared_ptr<Viga> viga = rta->popViga(0); // tomo la unica viga que inserte

    // printf("%u %u\n", viga->x_pos(), viga->y_pos());

    ASSERT_TRUE(viga->x_pos() == x && viga->y_pos() == y && viga->return_ancho() == ancho && viga->return_alto() == alto && viga->return_angulo() == angulo);
}

TEST(PROTOCOLOCLIENTE__RECIBIR, __Multiples_vigas)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));
    bool was_closed = false;

    skt.sendall(&VIGA_CODE, sizeof(VIGA_CODE), &was_closed);
    uint8_t cant = 3; // hago como que le envie una lista con una sola viga
    skt.sendall(&cant, sizeof(cant), &was_closed);

    uint16_t x_1 = 20;
    uint16_t y_1 = 10;
    uint16_t ancho_1 = 10;
    uint16_t alto_1 = 10;
    uint16_t angulo_1 = 45;
    enviar_viga_con_parametros(std::ref(skt), x_1, y_1, ancho_1, alto_1, angulo_1);
    uint16_t x_2 = 65;
    uint16_t y_2 = 56;
    uint16_t ancho_2 = 96;
    uint16_t alto_2 = 76;
    uint16_t angulo_2 = 20;
    enviar_viga_con_parametros(std::ref(skt), x_2, y_2, ancho_2, alto_2, angulo_2);
    uint16_t x_3 = 26;
    uint16_t y_3 = 16;
    uint16_t ancho_3 = 16;
    uint16_t alto_3 = 16;
    uint16_t angulo_3 = 46;
    enviar_viga_con_parametros(std::ref(skt), x_3, y_3, ancho_3, alto_3, angulo_3);

    std::shared_ptr<Vigas> rta = std::dynamic_pointer_cast<Vigas>(cp.receive(was_closed));
    std::shared_ptr<Viga> viga1 = rta->popViga(0);
    std::shared_ptr<Viga> viga2 = rta->popViga(1);
    std::shared_ptr<Viga> viga3 = rta->popViga(2);

    ASSERT_TRUE(viga1->x_pos() == x_1 && viga1->y_pos() == y_1 && viga1->return_ancho() == ancho_1 && viga1->return_alto() == alto_1 && viga1->return_angulo() == angulo_1);

    ASSERT_TRUE(viga2->x_pos() == x_2 && viga2->y_pos() == y_2 && viga2->return_ancho() == ancho_2 && viga2->return_alto() == alto_2 && viga2->return_angulo() == angulo_2);

    ASSERT_TRUE(viga3->x_pos() == x_3 && viga3->y_pos() == y_3 && viga3->return_ancho() == ancho_3 && viga3->return_alto() == alto_3 && viga3->return_angulo() == angulo_3);
}

void enviar_gusano_con_parametros(SocketMock &skt, uint8_t id, uint16_t x, uint16_t y, uint8_t vida, uint8_t color)
{
    bool was_closed = false;

    uint16_t x_a_enviar = htons(x);
    uint16_t y_a_enviar = htons(y);
    uint8_t id_a_enviar = id;
    uint8_t vida_a_enviar = vida;
    uint8_t color_a_enviar = color;

    // printf("%u %u\n", x, y);
    // printf("%u %u\n", x_a_enviar, y_a_enviar);

    skt.sendall(&id_a_enviar, sizeof(id_a_enviar), &was_closed);
    skt.sendall(&x_a_enviar, sizeof(x_a_enviar), &was_closed);
    skt.sendall(&y_a_enviar, sizeof(y_a_enviar), &was_closed);
    skt.sendall(&vida_a_enviar, sizeof(vida_a_enviar), &was_closed);
    skt.sendall(&color_a_enviar, sizeof(color_a_enviar), &was_closed);
}

TEST(PROTOCOLOCLIENTE__RECIBIR, __Gusano)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;
    uint8_t id = 8;
    uint16_t x = 20;
    uint16_t y = 10;
    uint8_t vida = 80;
    uint8_t color = 1;

    skt.sendall(&GUSANO_CODE, sizeof(GUSANO_CODE), &was_closed);
    enviar_gusano_con_parametros(std::ref(skt), id, x, y, vida, color);

    std::shared_ptr<Gusano> rta = std::dynamic_pointer_cast<Gusano>(cp.receive(was_closed));

    // ASSERT_TRUE(rta->x_pos() == x && rta->y_pos() == y && rta->get_id() == id && rta->get_vida() == vida);
    ASSERT_TRUE(rta->x_pos() == x);
    ASSERT_TRUE(rta->y_pos() == y);
    ASSERT_TRUE(rta->get_id() == id);
    ASSERT_TRUE(rta->get_vida() == vida);
    ASSERT_TRUE(rta->get_color() == color);
}

TEST(PROTOCOLOCLIENTE__RECIBIR, varios_gusanos)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;

    skt.sendall(&GUSANOS_CODE, sizeof(GUSANOS_CODE), &was_closed);
    uint8_t cant = 3;
    skt.sendall(&cant, sizeof(cant), &was_closed);
    uint8_t turno = 3;
    skt.sendall(&turno, sizeof(turno), &was_closed);
    uint8_t flag = 1;
    skt.sendall(&flag, sizeof(flag), &was_closed);

    uint8_t id_1 = 8;
    uint16_t x_1 = 20;
    uint16_t y_1 = 10;
    uint8_t vida_1 = 80;
    uint8_t color_1 = 1;
    enviar_gusano_con_parametros(std::ref(skt), id_1, x_1, y_1, vida_1, color_1);

    uint8_t id_2 = 8;
    uint16_t x_2 = 20;
    uint16_t y_2 = 10;
    uint8_t vida_2 = 80;
    uint8_t color_2 = 2;
    enviar_gusano_con_parametros(std::ref(skt), id_2, x_2, y_2, vida_2, color_2);

    uint8_t id_3 = 8;
    uint16_t x_3 = 20;
    uint16_t y_3 = 10;
    uint8_t vida_3 = 80;
    uint8_t color_3 = 3;
    enviar_gusano_con_parametros(std::ref(skt), id_3, x_3, y_3, vida_3, color_3);

    std::shared_ptr<Gusanos> rta = std::dynamic_pointer_cast<Gusanos>(cp.receive(was_closed)); // recibo
    std::shared_ptr<Gusano> g1 = rta->popGusano(0);
    std::shared_ptr<Gusano> g2 = rta->popGusano(1);
    std::shared_ptr<Gusano> g3 = rta->popGusano(2);

    ASSERT_TRUE(rta->get_flag_proyectil() == true && rta->cantidad() == 3);
    ASSERT_TRUE(g1->x_pos() == x_1 && g1->y_pos() == y_1 && g1->get_id() == id_1 && g1->get_vida() == vida_1 && g1->get_color() == color_1);
    ASSERT_TRUE(g2->x_pos() == x_2 && g2->y_pos() == y_2 && g2->get_id() == id_2 && g2->get_vida() == vida_2 && g2->get_color() == color_2);
    ASSERT_TRUE(g3->x_pos() == x_3 && g3->y_pos() == y_3 && g3->get_id() == id_3 && g3->get_vida() == vida_3 && g3->get_color() == color_3);
    // ASSERT_TRUE(rta->y_pos() == y);
    // ASSERT_TRUE(rta->get_id() == id);
    // ASSERT_TRUE(rta->get_vida() == vida);
}

TEST(PROTOCOLOCLIENTE__RECIBIR, __GranadaVerde)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;

    skt.sendall(&GRANADA_VERDE_CODE, sizeof(GRANADA_VERDE_CODE), &was_closed);

    uint16_t x = 30;
    x = htons(x);
    skt.sendall(&x, sizeof(x), &was_closed);

    uint16_t y = 10;
    y = htons(y);
    skt.sendall(&y, sizeof(y), &was_closed);

    std::shared_ptr<Proyectil> rta = std::dynamic_pointer_cast<Proyectil>(cp.receive(was_closed)); // recibo

    ASSERT_TRUE(ntohs(rta->x_pos()) == x);
    ASSERT_TRUE(ntohs(rta->y_pos()) == y);
    // ASSERT_TRUE(rta->get_id() == id);
    // ASSERT_TRUE(rta->get_vida() == vida);
}

TEST(PROTOCOLOCLIENTE__RECIBIR, __Bazooka)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;

    skt.sendall(&BAZUKA_CODE, sizeof(BAZUKA_CODE), &was_closed);

    uint16_t x = 30;
    x = htons(x);
    skt.sendall(&x, sizeof(x), &was_closed);

    uint16_t y = 10;
    y = htons(y);
    skt.sendall(&y, sizeof(y), &was_closed);

    uint8_t angulo = 27;
    skt.sendall(&angulo, sizeof(angulo), &was_closed);

    std::shared_ptr<Proyectil> rta = std::dynamic_pointer_cast<Proyectil>(cp.receive(was_closed)); // recibo

    ASSERT_TRUE(ntohs(rta->x_pos()) == x);
    ASSERT_TRUE(ntohs(rta->y_pos()) == y);
    ASSERT_TRUE(rta->get_angulo() == angulo);
    // ASSERT_TRUE(rta->get_id() == id);
    // ASSERT_TRUE(rta->get_vida() == vida);
}

void printServidor()
{
    std::cout << "**********************************************************************************************************************\n";
    std::cout << "*                                   PRUEBAS PROTOCOLO SERVIDOR                                                       *\n";
    std::cout << "**********************************************************************************************************************\n";
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, __IdDelCliente)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    std::shared_ptr<ClienteId> cliente = std::make_shared<ClienteId>(5);
    sp.enviarId(cliente, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    uint8_t id_recibido;
    skt->recvall(&id_recibido, sizeof(id_recibido), &was_closed);

    delete skt;
    ASSERT_TRUE(code == CLIENTE_ID_CODE && id_recibido == 5);
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, __IdFinDePartida)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    std::shared_ptr<Dto> dto = std::make_shared<Dto>(FINALIZAR_CODE);
    sp.enviarFinalizarPartida(dto, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    delete skt;
    ASSERT_TRUE(code == FINALIZAR_CODE);
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, ___IniciodePartida)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    std::shared_ptr<Dto> dto = std::make_shared<Dto>(INICIAR_PARIDA);
    sp.enviarIniciarPartida(dto, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    delete skt;
    ASSERT_TRUE(code == INICIAR_PARIDA);
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, __ListadePartidas)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;
    uint8_t cant_enviada = 2;
    uint8_t op1 = 20;
    uint8_t op2 = 11;

    std::shared_ptr<ListaDePartidas> lista_de_partidas = std::make_shared<ListaDePartidas>();
    lista_de_partidas->addOption(op1);
    lista_de_partidas->addOption(op2);

    sp.enviarListaDePartidas(lista_de_partidas, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    uint8_t cant;
    skt->recvall(&cant, sizeof(cant), &was_closed);

    uint8_t op1_recibida;
    skt->recvall(&op1_recibida, sizeof(op1_recibida), &was_closed);

    uint8_t op2_recibida;
    skt->recvall(&op2_recibida, sizeof(op2_recibida), &was_closed);

    delete skt;
    ASSERT_TRUE(code == LISTA_DE_PARTIDAS_CODE);
    ASSERT_TRUE(cant == cant_enviada);
    ASSERT_TRUE(op1_recibida == op1);
    ASSERT_TRUE(op2_recibida == op2);
}

void recibir_parametros_del_gusano(SocketMock *skt, uint8_t &id, uint16_t &x, uint16_t &y, uint8_t &vida, uint8_t &color)
{
    bool was_closed = false;

    uint16_t x_recibido;
    uint16_t y_recibido;
    uint8_t id_recibido;
    uint8_t vida_recibido;
    uint8_t color_recibido;

    skt->recvall(&id_recibido, sizeof(id_recibido), &was_closed);
    skt->recvall(&x_recibido, sizeof(x_recibido), &was_closed);
    skt->recvall(&y_recibido, sizeof(y_recibido), &was_closed);
    skt->recvall(&vida_recibido, sizeof(vida_recibido), &was_closed);
    skt->recvall(&color_recibido, sizeof(color_recibido), &was_closed);

    id = id_recibido;
    x = ntohs(x_recibido);
    y = ntohs(y_recibido);
    vida = vida_recibido;
    color = color_recibido;
    // printf("%u %u %u %u %u\n", id, x, y, vida, color);
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, __Gusano)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 2;
    uint16_t x = 20;
    uint16_t y = 11;
    uint8_t vida = 85;
    uint8_t color = 3;

    std::shared_ptr<Gusano> gusano = std::make_shared<Gusano>(id, x, y, vida, color);

    sp.enviarGusano(gusano, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    uint8_t id_recibido;
    uint16_t x_recibido;
    uint16_t y_recibido;
    uint8_t vida_recibida;
    uint8_t color_recibido;

    recibir_parametros_del_gusano(skt, id_recibido, x_recibido, y_recibido, vida_recibida, color_recibido);

    delete skt;
    ASSERT_TRUE(code == GUSANO_CODE);
    ASSERT_TRUE(id_recibido == id);
    ASSERT_TRUE(x_recibido == x);
    ASSERT_TRUE(y_recibido == y);
    ASSERT_TRUE(vida_recibida == vida);
    ASSERT_TRUE(color_recibido == color);
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, __Multiples_gusanos)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id_enviada1 = 2;
    uint16_t x_enviada1 = 20;
    uint16_t y_enviada1 = 11;
    uint8_t vida_enviada1 = 85;
    uint8_t color_enviada1 = 3;
    std::shared_ptr<Gusano> gusano1 = std::make_shared<Gusano>(id_enviada1, x_enviada1, y_enviada1, vida_enviada1, color_enviada1);

    uint8_t id_enviada2 = 3;
    uint16_t x_enviada2 = 24;
    uint16_t y_enviada2 = 15;
    uint8_t vida_enviada2 = 86;
    uint8_t color_enviada2 = 10;
    std::shared_ptr<Gusano> gusano2 = std::make_shared<Gusano>(id_enviada2, x_enviada2, y_enviada2, vida_enviada2, color_enviada2);

    uint8_t id_enviada3 = 6;
    uint16_t x_enviada3 = 54;
    uint16_t y_enviada3 = 75;
    uint8_t vida_enviada3 = 16;
    uint8_t color_enviada3 = 11;
    std::shared_ptr<Gusano> gusano3 = std::make_shared<Gusano>(id_enviada3, x_enviada3, y_enviada3, vida_enviada3, color_enviada3);

    std::vector<std::shared_ptr<Gusano>> lista;
    lista.push_back(gusano1);
    lista.push_back(gusano2);
    lista.push_back(gusano3);
    std::shared_ptr<Gusanos> gusanos = std::make_shared<Gusanos>(lista);

    sp.enviarListaDeGusanos(gusanos, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    uint8_t cant;
    skt->recvall(&cant, sizeof(cant), &was_closed);

    uint8_t turno;
    skt->recvall(&turno, sizeof(turno), &was_closed);

    uint8_t flag;
    skt->recvall(&flag, sizeof(flag), &was_closed);

    uint8_t id_1;
    uint16_t x_1;
    uint16_t y_1;
    uint8_t vida_1;
    uint8_t color_1;
    recibir_parametros_del_gusano(std::ref(skt), id_1, x_1, y_1, vida_1, color_1);

    uint8_t id_2;
    uint16_t x_2;
    uint16_t y_2;
    uint8_t vida_2;
    uint8_t color_2;
    recibir_parametros_del_gusano(std::ref(skt), id_2, x_2, y_2, vida_2, color_2);

    uint8_t id_3;
    uint16_t x_3;
    uint16_t y_3;
    uint8_t vida_3;
    uint8_t color_3;
    recibir_parametros_del_gusano(std::ref(skt), id_3, x_3, y_3, vida_3, color_3);

    delete skt;
    ASSERT_TRUE(code == GUSANOS_CODE && cant == 3 && turno == 1 && flag == 0);
    ASSERT_TRUE(id_1 == id_enviada1 && x_1 == x_enviada1 && y_1 == y_enviada1 && vida_1 == vida_enviada1 && color_1 == color_enviada1);
    ASSERT_TRUE(id_2 == id_enviada2 && x_2 == x_enviada2 && y_2 == y_enviada2 && vida_2 == vida_enviada2 && color_2 == color_enviada2);
    ASSERT_TRUE(id_3 == id_enviada3 && x_3 == x_enviada3 && y_3 == y_enviada3 && vida_3 == vida_enviada3 && color_3 == color_enviada3);
}

void recibir_parametros_de_la_viga(SocketMock *skt, uint16_t &x, uint16_t &y, uint16_t &ancho, uint16_t &alto, uint16_t &angulo)
{
    bool was_closed = false;

    uint16_t x_recibido;
    uint16_t y_recibido;
    uint16_t ancho_recibido;
    uint16_t alto_recibido;
    uint16_t angulo_recibido;

    skt->recvall(&x_recibido, sizeof(x_recibido), &was_closed);
    skt->recvall(&y_recibido, sizeof(y_recibido), &was_closed);
    skt->recvall(&ancho_recibido, sizeof(ancho_recibido), &was_closed);
    skt->recvall(&alto_recibido, sizeof(alto_recibido), &was_closed);
    skt->recvall(&angulo_recibido, sizeof(angulo_recibido), &was_closed);

    x = ntohs(x_recibido);
    y = ntohs(y_recibido);
    ancho = ntohs(ancho_recibido);
    alto = ntohs(alto_recibido);
    angulo = ntohs(angulo_recibido);
    // printf("%u %u %u %u %u\n", id, x, y, vida, color);
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, ListadeVigas)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint16_t x_enviada1 = 20;
    uint16_t y_enviada1 = 11;
    uint16_t ancho_enviada1 = 2;
    uint16_t alto_enviada1 = 85;
    uint16_t angulo_enviada1 = 3;
    std::shared_ptr<Viga> viga1 = std::make_shared<Viga>(x_enviada1, y_enviada1, ancho_enviada1, alto_enviada1, angulo_enviada1);

    uint16_t ancho_enviada2 = 3;
    uint16_t x_enviada2 = 24;
    uint16_t y_enviada2 = 15;
    uint16_t alto_enviada2 = 86;
    uint16_t angulo_enviada2 = 10;
    std::shared_ptr<Viga> viga2 = std::make_shared<Viga>(x_enviada2, y_enviada2, ancho_enviada2, alto_enviada2, angulo_enviada2);

    uint16_t ancho_enviada3 = 6;
    uint16_t x_enviada3 = 54;
    uint16_t y_enviada3 = 75;
    uint16_t alto_enviada3 = 16;
    uint16_t angulo_enviada3 = 11;
    std::shared_ptr<Viga> viga3 = std::make_shared<Viga>(x_enviada3, y_enviada3, ancho_enviada3, alto_enviada3, angulo_enviada3);

    std::vector<std::shared_ptr<Viga>> lista;
    lista.push_back(viga1);
    lista.push_back(viga2);
    lista.push_back(viga3);
    std::shared_ptr<Vigas> vigas = std::make_shared<Vigas>(lista);

    sp.enviarVigas(vigas, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    uint8_t cant;
    skt->recvall(&cant, sizeof(cant), &was_closed);

    uint16_t x_1;
    uint16_t y_1;
    uint16_t ancho_1;
    uint16_t alto_1;
    uint16_t angulo_1;
    recibir_parametros_de_la_viga(std::ref(skt), x_1, y_1, ancho_1, alto_1, angulo_1);

    uint16_t x_2;
    uint16_t y_2;
    uint16_t ancho_2;
    uint16_t alto_2;
    uint16_t angulo_2;
    recibir_parametros_de_la_viga(std::ref(skt), x_2, y_2, ancho_2, alto_2, angulo_2);

    uint16_t x_3;
    uint16_t y_3;
    uint16_t ancho_3;
    uint16_t alto_3;
    uint16_t angulo_3;
    recibir_parametros_de_la_viga(std::ref(skt), x_3, y_3, ancho_3, alto_3, angulo_3);

    delete skt;
    ASSERT_TRUE(code == VIGA_CODE && cant == 3);
    ASSERT_TRUE(x_1 == x_enviada1 && y_1 == y_enviada1 && ancho_1 == ancho_enviada1 && alto_1 == alto_enviada1 && angulo_1 == angulo_enviada1);
    ASSERT_TRUE(x_2 == x_enviada2 && y_2 == y_enviada2 && ancho_2 == ancho_enviada2 && alto_2 == alto_enviada2 && angulo_2 == angulo_enviada2);
    ASSERT_TRUE(x_3 == x_enviada3 && y_3 == y_enviada3 && ancho_3 == ancho_enviada3 && alto_3 == alto_enviada3 && angulo_3 == angulo_enviada3);
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, TrayectoriaGranadaVerde)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint16_t x_enviada = 20;
    uint16_t y_enviada = 11;
    std::shared_ptr<GranadaVerde> g = std::make_shared<GranadaVerde>(x_enviada, y_enviada);

    sp.enviarTrayectoriaDeGranadaVerde(g, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    uint16_t x;
    skt->recvall(&x, sizeof(x), &was_closed);
    x = ntohs(x);

    uint16_t y;
    skt->recvall(&y, sizeof(y), &was_closed);
    y = ntohs(y);

    delete skt;
    ASSERT_TRUE(code == GRANADA_VERDE_CODE);
    ASSERT_TRUE(x == x_enviada);
    ASSERT_TRUE(y == y_enviada);
}

TEST(PROTOCOLOSERVIDOR__ENVIAR, TrayectoriaBazooka)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint16_t x_enviada = 20;
    uint16_t y_enviada = 11;
    uint16_t angulo_enviado = 75;
    std::shared_ptr<Bazuka> g = std::make_shared<Bazuka>(x_enviada, y_enviada, angulo_enviado);

    sp.enviarTrayectoriaDeBazuka(g, was_closed);

    uint8_t code;
    skt->recvall(&code, sizeof(code), &was_closed);

    uint16_t x;
    skt->recvall(&x, sizeof(x), &was_closed);
    x = ntohs(x);

    uint16_t y;
    skt->recvall(&y, sizeof(y), &was_closed);
    y = ntohs(y);

    uint8_t angulo;
    skt->recvall(&angulo, sizeof(angulo), &was_closed);

    delete skt;
    ASSERT_TRUE(code == BAZUKA_CODE);
    ASSERT_TRUE(x == x_enviada);
    ASSERT_TRUE(y == y_enviada);
    ASSERT_TRUE(angulo == angulo_enviado);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(PROTOCOLOSERVIDOR__RECIBIR, __PartidaSeleccionada)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 4;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = LISTA_DE_PARTIDAS_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    uint8_t op = 6;
    skt->sendall(&op, sizeof(op), &was_closed);

    std::shared_ptr<ListaDePartidas> selec = std::dynamic_pointer_cast<ListaDePartidas>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(op == selec->seleccionada);
}

TEST(PROTOCOLOSERVIDOR__RECIBIR, __MoveraDerecha)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 4;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = MOVER_A_DERECHA_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    std::shared_ptr<MoverADerecha> rta = std::dynamic_pointer_cast<MoverADerecha>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(id == rta->get_cliente_id());
}

TEST(PROTOCOLOSERVIDOR__RECIBIR, __MoveraIzquierda)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 25;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = MOVER_A_IZQUIERDA_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    std::shared_ptr<MoverAIzquierda> rta = std::dynamic_pointer_cast<MoverAIzquierda>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(id == rta->get_cliente_id());
}

TEST(PROTOCOLOSERVIDOR__RECIBIR, __FindePartida)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 25;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = FINALIZAR_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    std::shared_ptr<Dto> rta = std::dynamic_pointer_cast<Dto>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(code == rta->return_code());
    ASSERT_TRUE(id == rta->get_cliente_id());
}

TEST(PROTOCOLOSERVIDOR__RECIBIR, __NuevaPartida)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 60;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = NUEVA_PARTIDA_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    uint8_t jugadores = 4;
    skt->sendall(&jugadores, sizeof(jugadores), &was_closed);

    std::shared_ptr<NuevaPartida> rta = std::dynamic_pointer_cast<NuevaPartida>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(code == rta->return_code());
    ASSERT_TRUE(jugadores == rta->get_cantidad_de_jugadores());
}

TEST(PROTOCOLOSERVIDOR__RECIBIR, __Salto)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 60;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = SALTAR_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    std::shared_ptr<Saltar> rta = std::dynamic_pointer_cast<Saltar>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(code == rta->return_code());
    ASSERT_TRUE(id == rta->get_cliente_id());
}

TEST(PROTOCOLOSERVIDOR__RECIBIR, __AtaqueconBate)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 2;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = BATEAR_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    uint8_t angulo = 25;
    skt->sendall(&angulo, sizeof(angulo), &was_closed);

    std::shared_ptr<Batear> rta = std::dynamic_pointer_cast<Batear>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(code == rta->return_code());
    ASSERT_TRUE(id == rta->get_cliente_id());
    ASSERT_TRUE(angulo == rta->get_angulo());
}

TEST(PROTOCOLOSERVIDOR__RECIBIR, __AtaqueconGranadaVerde)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 2;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = GRANADA_VERDE_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    uint8_t potencia = 25;
    skt->sendall(&potencia, sizeof(potencia), &was_closed);

    uint8_t angulo = 25;
    skt->sendall(&angulo, sizeof(angulo), &was_closed);

    uint8_t tiempo = 5;
    skt->sendall(&tiempo, sizeof(tiempo), &was_closed);

    std::shared_ptr<GranadaVerde> rta = std::dynamic_pointer_cast<GranadaVerde>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(code == rta->return_code());
    ASSERT_TRUE(id == rta->get_cliente_id());
    ASSERT_TRUE(potencia == rta->get_potencia());
    ASSERT_TRUE(angulo == rta->get_angulo());
    ASSERT_TRUE(tiempo == rta->get_tiempo());
}

TEST(PROTOCOLOSERVIDOR__RECIBIR, __AtaqueconBazooka)
{
    SocketMock *skt = new SocketMock();
    ServerProtocol sp(skt);
    bool was_closed = false;

    uint8_t id = 2;
    skt->sendall(&id, sizeof(id), &was_closed);

    uint8_t code = BAZUKA_CODE;
    skt->sendall(&code, sizeof(code), &was_closed);

    uint8_t potencia = 25;
    skt->sendall(&potencia, sizeof(potencia), &was_closed);

    uint8_t angulo = 25;
    skt->sendall(&angulo, sizeof(angulo), &was_closed);

    std::shared_ptr<Bazuka> rta = std::dynamic_pointer_cast<Bazuka>(sp.recibirActividad(was_closed));

    delete skt;
    ASSERT_TRUE(code == rta->return_code());
    ASSERT_TRUE(id == rta->get_cliente_id());
    ASSERT_TRUE(potencia == rta->get_potencia());
    ASSERT_TRUE(angulo == rta->get_angulo());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
