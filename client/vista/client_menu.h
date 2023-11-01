#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <exception>
#include <algorithm>

#include <SDL2pp/SDL2pp.hh>

#include "client.h"

using namespace SDL2pp;

class Menu
{
private:
    Client &cliente;

public:
    Menu(Client &cliente);

    int iniciar();
    bool handleEvents();
    void renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &background, SDL2pp::Texture &boton, SDL2pp::Font &font);
};

#endif