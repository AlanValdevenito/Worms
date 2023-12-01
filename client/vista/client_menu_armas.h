#ifndef MENU_ARMAS_H
#define MENU_ARMAS_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class MenuArmas
{

private:
    std::map<int, std::unique_ptr<SDL2pp::Texture>> armas;
    int abierto;

    SDL2pp::Font fuente;

public:
    MenuArmas(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer);
    void abrirMenu();
};

#endif // MENU_ARMAS_H
