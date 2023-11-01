#ifndef VISTA_H
#define VISTA_H 

#include "client_menu.h"
#include "client_partida_vista.h"

class Vista
{
private:
    Client &cliente;
    
    Menu menu;
    PartidaVista partida;

public:
    Vista(Client &cliente);

    int iniciar();
};

#endif
