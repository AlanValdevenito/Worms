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
#include "dto.h"
#include "dead.h"
#include "viga.h"
#include "gusano.h"
#include "mover.h"

const uint8_t VIGAS_CODE = 1;
const uint8_t GUSANO_CODE = 2;
// const uint8_t MOVER_A_DERECHA_CODE = 3;

class ClientProtocol
{
public:
    explicit ClientProtocol(Socket &skt);
    ~ClientProtocol();
    void send(bool &was_closed);
    Dto *receive(bool &was_closed);
    void moverADerecha(MoverADerecha *m, bool &was_closed);

private:
    Socket &skt;
    Dto *receiveViga(bool &was_closed);
    Dto *receiveVigas(bool &was_closed);
    Dto *receiveGusano(bool &was_closed);
};
#endif
