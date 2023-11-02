#ifndef VISTA_H
#define VISTA_H

#include "client_menu.h"
#include "client_partida.h"

class Vista
{
private:
    Client &cliente;

    Menu menu;
    Partida partida;

public:
    Vista(Client &cliente);

    int iniciar();
};

#endif
