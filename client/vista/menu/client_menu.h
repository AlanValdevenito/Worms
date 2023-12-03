#ifndef MENU_H
#define MENU_H

#include "client.h"

class Menu {
private:
    Client &cliente;

public:
    Menu(Client &cliente);

    int iniciar(int argc, char* argv[]);
};

#endif
