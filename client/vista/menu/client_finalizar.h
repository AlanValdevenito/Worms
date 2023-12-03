#ifndef FINALIZAR_H
#define FINALIZAR_H

#include "client.h"

class Finalizar {
private:
    Client &cliente;

public:
    Finalizar(Client &cliente);

    int iniciar(int argc, char* argv[], int resultado = 0);
};

#endif
