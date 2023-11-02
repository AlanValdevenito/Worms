#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <netinet/in.h>

#include "dto.h"
#include "dead.h"
#include "gusano.h"
#include "viga.h"
#include "mover.h"
#include "partidas_lista.h"
#include "cliente_id.h"
#include "socket.h"

class ServerProtocol
{
public:
    explicit ServerProtocol(Socket &skt);
    ~ServerProtocol();
    std::shared_ptr<Dto> recv(bool &was_closed);
    void sendId(std::shared_ptr<ClienteId> id, bool &was_closed);
    void sendVigas(std::shared_ptr<Dto> vs, bool &was_closed);
    void sendWorms(std::shared_ptr<Gusano> g, bool &was_closed);
    void sendAllWorms(std::shared_ptr<Gusanos> gs, bool &was_closed);
    void sendPartidas(std::shared_ptr<ListaDePartidas> l, bool &was_closed);
    void sendIniciarPartida(std::shared_ptr<Dto> dto, bool &was_closed);

private:
    Socket &skt;
    void sendViga(std::shared_ptr<Dto> dto, bool &was_closed);
    std::shared_ptr<Dto> recvPartidaSeleccionada(uint8_t id, bool &was_closed);
    // std::shared_ptr<Dto>recv_message(bool &was_closed, uint16_t sz, uint8_t code);
};
#endif
