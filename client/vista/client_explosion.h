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
    Animation fuego;

    int movimientoFuego;

public:
    Explosion(SDL2pp::Renderer &renderer);

    void update();
    void render(SDL2pp::Renderer &renderer, float x, float y, float camaraLimiteIzquierdo, float camaraLimiteSuperior); // Renderiza el arma.
    bool animacion_completa();
};

#endif // EXPLOSION_H
