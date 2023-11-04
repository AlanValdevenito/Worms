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

#include "blockingqueue.h"
#include "dto.h"
#include "dead.h"
#include "gusano.h"
#include "mover.h"
#include "batear.h"
#include "partidas_lista.h"
#include "cliente_id.h"
#include "socket.h"

class ServerProtocol
{
public:
    explicit ServerProtocol(Socket &skt);
    ~ServerProtocol();
    std::shared_ptr<Dto> recibirActividad(bool &was_closed);
    bool enviarId(std::shared_ptr<ClienteId> id, bool &was_closed);
    bool enviarVigas(std::shared_ptr<Dto> vs, bool &was_closed);
    bool enviarGusano(std::shared_ptr<Gusano> g, bool &was_closed);
    bool enviarListaDeGusanos(std::shared_ptr<Gusanos> gs, bool &was_closed);
    bool enviarListaDePartidas(std::shared_ptr<ListaDePartidas> l, bool &was_closed);
    bool enviarIniciarPartida(std::shared_ptr<Dto> dto, bool &was_closed);
    bool enviarFinalizarPartida(std::shared_ptr<Dto> dto, bool &was_closed);

private:
    Socket &skt;
    std::shared_ptr<Dto> recibirPartidaSeleccionada(uint8_t id, bool &was_closed);
    std::shared_ptr<Dto> recibirAtaqueConBate(uint8_t id, bool &was_closed);
    bool enviarViga(std::shared_ptr<Dto> dto, bool &was_closed);
    bool enviarDatosDelGusano(std::shared_ptr<Gusano> g, bool &was_closed);
    bool enviarCodigoDeElemento(std::shared_ptr<Dto> dto, bool &was_closed);
};
#endif
