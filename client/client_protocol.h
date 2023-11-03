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
#include "constantes.h"
#include "dto.h"
#include "dead.h"
#include "viga.h"
#include "gusano.h"
#include "mover.h"
#include "batear.h"
#include "partidas_lista.h"
#include "cliente_id.h"

class ClientProtocol
{
public:
    explicit ClientProtocol(Socket &skt);
    ~ClientProtocol();
    void send(bool &was_closed);
    std::shared_ptr<Dto> receive(bool &was_closed);
    void moverADerecha(std::shared_ptr<MoverADerecha> m, bool &was_closed);
    void moverAIzquierda(std::shared_ptr<MoverAIzquierda> m, bool &was_closed);
    void enviarSeleccion(std::shared_ptr<ListaDePartidas> l, bool &was_closed);
    void enviarAtaqueConBate(std::shared_ptr<Batear> b, bool &was_closed);

private:
    Socket &skt;
    std::shared_ptr<Viga> receiveViga(bool &was_closed);
    std::shared_ptr<Dto> receiveVigas(bool &was_closed);
    std::shared_ptr<Gusano> receiveGusano(bool &was_closed);
    std::shared_ptr<Dto> receiveGusanos(bool &was_closed);
    std::shared_ptr<Dto> receivePartidas(bool &was_closed);
    std::shared_ptr<Dto> receiveId(bool &was_closed);
};
#endif
