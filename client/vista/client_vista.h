#ifndef VISTA_H
#define VISTA_H

#include "client_menu.h"
#include "client_partida.h"
#include "client_finalizar.h"

class Vista
{
private:
    Client &cliente;

    Menu menu;
    Partida partida;
    Finalizar finalizar;

public:
    Vista(Client &cliente);

    int iniciar(int argc, char* argv[]);
};

#endif
