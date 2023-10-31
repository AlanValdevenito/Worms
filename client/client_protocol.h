#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <netinet/in.h>

#include "socket.h"
#include "constantes.h"
#include "dto.h"
#include "dead.h"
#include "viga.h"
#include "gusano.h"
#include "mover.h"
#include "partidas_lista.h"
#include "cliente_id.h"

class ClientProtocol
{
public:
    explicit ClientProtocol(Socket &skt);
    ~ClientProtocol();
    void send(bool &was_closed);
    Dto *receive(bool &was_closed);
    void moverADerecha(MoverADerecha *m, bool &was_closed);
    void moverAIzquierda(MoverAIzquierda *m, bool &was_closed);
    void enviarSeleccion(ListaDePartidas *l, bool &was_closed);

private:
    Socket &skt; 
    Dto *receiveViga(bool &was_closed);
    Dto *receiveVigas(bool &was_closed);
    Dto *receiveGusano(bool &was_closed);
    Dto *receivePartidas(bool &was_closed);
    Dto* receiveId(bool &was_closed);
};
#endif
