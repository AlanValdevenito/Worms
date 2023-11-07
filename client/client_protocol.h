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
#include "constantes.h"
#include "dto.h"
#include "dead.h"
#include "viga.h"
#include "gusano.h"
#include "mover.h"
#include "batear.h"
#include "partidas_lista.h"
#include "nueva_partida.h"
#include "cliente_id.h"

class ClientProtocol
{
public:
    explicit ClientProtocol(Socket &skt);
    ~ClientProtocol();
    std::shared_ptr<Dto> receive(bool &was_closed);
    bool moverADerecha(std::shared_ptr<MoverADerecha> m, bool &was_closed);
    bool moverAIzquierda(std::shared_ptr<MoverAIzquierda> m, bool &was_closed);
    bool enviarSeleccion(std::shared_ptr<ListaDePartidas> l, bool &was_closed);
    bool enviarAtaqueConBate(std::shared_ptr<Batear> b, bool &was_closed);
    bool enviarFinDePartida(std::shared_ptr<Dto> dto, bool &was_closed);
    bool saltar(std::shared_ptr<Dto> s, bool &was_closed);
    bool enviarNuevaPartida(std::shared_ptr<NuevaPartida> n, bool &was_closed);

    void sendPruebita(uint8_t a);
    void recvPruebita();

private:
    Socket &skt;
    std::shared_ptr<Dto> recibirViga(bool &was_closed);
    std::shared_ptr<Dto> recibirVigas(bool &was_closed);
    std::shared_ptr<Dto> recibirGusano(bool &was_closed);
    std::shared_ptr<Dto> recibirGusanos(bool &was_closed);
    std::shared_ptr<Dto> recibirPartidas(bool &was_closed);
    std::shared_ptr<Dto> recibirId(bool &was_closed);
    std::shared_ptr<Dto> recibirTurnoDeGusano(bool &was_closed);
    bool enviarIdDelClienteYCodigoDeAccion(std::shared_ptr<Dto> dto, bool &was_closed);
    bool recibirPosicion(uint16_t &x, uint16_t &y, bool &was_closed);
    uint8_t cantidadARecibir(bool &was_closed);
};
#endif
