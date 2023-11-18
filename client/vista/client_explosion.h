#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "client_animacion.h"

#include <SDL2pp/SDL2pp.hh>

class Explosion
{

private:
    std::shared_ptr<SDL2pp::Texture> texture; // Atributo que almacena la textura de la animacion

    Animation biff;
    Animation circulo;
    Animation elipse;

public:
    Explosion(SDL2pp::Renderer &renderer);

    void update();
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest); // Renderiza el arma.
};

#endif // EXPLOSION_H
