#include <gtest/gtest.h>
#include "socket_mock.h"
#include "client.h"
#include "client_protocol.h"
#include "server_protocol.h"
#include "constantes.h"
#include "mover.h"

TEST(Test1, Envio_Mover_a_Derecha)
{

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

TEST(Test2, Envio_Mover_a_Izquierda)
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

TEST(Test3, Envio_de_seleccion_de_partida)
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

TEST(Test4, Envio_ataque_con_bate)
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

TEST(Test5, Envio_de_aviso_de_fin_de_partida)
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

TEST(Test6, Envio_de_salto)
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

TEST(Test7, Envio_de_peticion_de_nueva_partida)
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

TEST(Test9, Recibir_id_de_cliente)
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

TEST(Test10, Recibir_lista_de_partidas)
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

TEST(Test11, Recibir_una_viga)
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

    ASSERT_TRUE(viga->x_pos() == x && viga->y_pos() == y && viga->return_ancho() == ancho && viga->return_alto() == alto && viga->return_angulo() == angulo);
}

TEST(Test12, Recibir_varias_vigas)
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

    skt.sendall(&id_a_enviar, sizeof(id_a_enviar), &was_closed);
    skt.sendall(&x_a_enviar, sizeof(x_a_enviar), &was_closed);
    skt.sendall(&y_a_enviar, sizeof(y_a_enviar), &was_closed);
    skt.sendall(&vida_a_enviar, sizeof(vida_a_enviar), &was_closed);
    skt.sendall(&color_a_enviar, sizeof(color_a_enviar), &was_closed);
}

TEST(Test13, Recibir_un_solo_gusano)
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

TEST(Test13, Recibir_un_varios_gusanos)
{
    SocketMock skt;
    ClientProtocol cp(std::ref(skt));

    bool was_closed = false;

    skt.sendall(&GUSANOS_CODE, sizeof(GUSANOS_CODE), &was_closed);
    uint8_t cant = 3;
    skt.sendall(&cant, sizeof(cant), &was_closed);
    uint8_t turno = 3;
    skt.sendall(&turno, sizeof(turno), &was_closed);

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

    std::shared_ptr<Gusanos> rta = std::dynamic_pointer_cast<Gusanos>(cp.receive(was_closed));
    std::shared_ptr<Gusano> g1 = rta->popGusano(0);
    std::shared_ptr<Gusano> g2 = rta->popGusano(1);
    std::shared_ptr<Gusano> g3 = rta->popGusano(2);

    ASSERT_TRUE(g1->x_pos() == x_1 && g1->y_pos() == y_1 && g1->get_id() == id_1 && g1->get_vida() == vida_1 && g1->get_color() == color_1);
    ASSERT_TRUE(g2->x_pos() == x_2 && g2->y_pos() == y_2 && g2->get_id() == id_2 && g2->get_vida() == vida_2 && g2->get_color() == color_2);
    ASSERT_TRUE(g3->x_pos() == x_3 && g3->y_pos() == y_3 && g3->get_id() == id_3 && g3->get_vida() == vida_3 && g3->get_color() == color_3);
    // ASSERT_TRUE(rta->x_pos() == x);
    // ASSERT_TRUE(rta->y_pos() == y);
    // ASSERT_TRUE(rta->get_id() == id);
    // ASSERT_TRUE(rta->get_vida() == vida);
}

TEST(A, a)
{
    std::cout << "**********************************************************************************************************************\n";
    std::cout << "*                                   PRUEBAS PROTOCOLO SERVIDOR                                                       *\n";
    std::cout << "**********************************************************************************************************************\n";
}

TEST(Test14, EnviarIdDelCliente)
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

TEST(Test15, EnviarIdFinDePartida)
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

TEST(Test16, Enviar_inicio_de_partida)
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

TEST(Test17, Enviar_lista_de_partidas)
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

TEST(Test17, Enviar_un_solo_gusano)
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

TEST(Test18, Enviar_una_lista_de_gusanos)
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
    ASSERT_TRUE(code == GUSANOS_CODE && cant == 3 && turno == 1);
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

TEST(Test19, Enviar_una_lista_de_vigas)
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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
