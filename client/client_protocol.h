#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include <netinet/in.h>

#include "socket.h"
#include "socket_mock.h"
#include "socket_interface.h"
#include "constantes.h"
#include "dto.h"
#include "dead.h"
#include "viga.h"
#include "saltar.h"
#include "gusano.h"
#include "mover.h"
#include "batear.h"
#include "granada.h"
#include "granada_santa.h"
#include "granada_roja.h"
#include "granada_banana.h"
#include "dinamita.h"
#include "mortero.h"
#include "teletransportar.h"
#include "bazuka.h"
#include "proyectil.h"
#include "cheats.h"
#include "ganador.h"
#include "fragmento.h"
#include "ataque_aereo.h"
#include "partidas_lista.h"
#include "nueva_partida.h"
#include "equipar_arma.h"
#include "cliente_id.h"

class ClientProtocol
{
public:
    explicit ClientProtocol(SocketInterface &skt);
    ~ClientProtocol();

    std::shared_ptr<Dto> recibir(bool &was_closed);
    bool moverADerecha(std::shared_ptr<MoverADerecha> m, bool &was_closed);
    bool moverAIzquierda(std::shared_ptr<MoverAIzquierda> m, bool &was_closed);
    bool enviarSeleccion(std::shared_ptr<ListaDePartidas> l, bool &was_closed);
    bool enviarAtaqueConBate(std::shared_ptr<Batear> b, bool &was_closed);
    bool enviarFinDePartida(std::shared_ptr<Dto> dto, bool &was_closed);
    bool saltar(std::shared_ptr<Saltar> s, bool &was_closed);
    bool enviarNuevaPartida(std::shared_ptr<NuevaPartida> n, bool &was_closed);
    bool enviarAtaqueConGranadaVerde(std::shared_ptr<GranadaVerde> g, bool &was_closed);
    bool enviarAtaqueConBazuka(std::shared_ptr<Bazuka> b, bool &was_closed);
    bool enviarAtaqueConMortero(std::shared_ptr<Mortero> b, bool &was_closed);
    bool enviarAtaqueConGranadaBanana(std::shared_ptr<GranadaBanana> g, bool &was_closed);
    bool enviarAtaqueConGranadaSanta(std::shared_ptr<GranadaSanta> g, bool &was_closed);
    bool enviarAtaqueConGranadaRoja(std::shared_ptr<GranadaRoja> g, bool &was_closed);
    bool enviarAtaqueConDinamita(std::shared_ptr<Dinamita> g, bool &was_closed);
    bool enviarTeletrasnportacion(std::shared_ptr<Teletransportar> t, bool &was_closed);
    bool enviarEquipadoDeArma(std::shared_ptr<EquiparArma> t, bool &was_closed);
    bool enviarAtaqueaereo(std::shared_ptr<Misil> t, bool &was_closed);
    bool enviarCheat(std::shared_ptr<Cheat> c, bool &was_closed);

    bool enviarAtaque(std::shared_ptr<Dto> dto, bool &was_closed);
    bool enviarMovimiento(std::shared_ptr<Dto> dto, bool &was_closed);

private:
    SocketInterface &skt;
    std::shared_ptr<Dto> recibirViga(bool &was_closed);
    std::shared_ptr<Dto> recibirVigas(bool &was_closed);
    std::shared_ptr<Dto> recibirGusano(bool &was_closed);
    std::shared_ptr<Dto> recibirGusanos(bool &was_closed);
    std::shared_ptr<Dto> recibirPartidas(bool &was_closed);
    std::shared_ptr<Dto> recibirGanador(bool &was_closed);
    std::shared_ptr<Dto> recibirId(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaGranadaVerde(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaGranadaSanta(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaGranadaBanana(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaGranadaRoja(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaDinamita(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaBazuka(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaMortero(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaMisil(bool &was_closed);
    std::shared_ptr<Dto> recibirTrayectoriaFragmento(bool &was_closed);
    std::shared_ptr<Dto> recibirProyectiles(bool &was_closed);
    std::shared_ptr<Dto> recibirProyectil(bool &was_closed);
    bool enviarIdDelClienteYCodigoDeAccion(std::shared_ptr<Dto> dto, bool &was_closed);
    bool enviarAnguloYPotenciaDeProyectil(std::shared_ptr<Proyectil> dto, bool &was_closed);
    bool enviarAtaqueConGranada(std::shared_ptr<Proyectil> g, bool &was_closed);
    bool recibirPosicion(uint16_t &x, uint16_t &y, bool &was_closed);
    uint8_t cantidadARecibir(bool &was_closed);
};
#endif
