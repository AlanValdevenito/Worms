#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <utility>

#include "client_protocolo.h"

class Cliente {
private:
    ProtocoloCliente protocolo;

public:
    explicit Cliente(Socket&& socket);

    void conectarse();
    void send(const Mensaje& mensaje);
    void recv(const int& cantidad);
    void imprimir(const Mensaje& mensaje);
    Mensaje parsear();
};

#endif
