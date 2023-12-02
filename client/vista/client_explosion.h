#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "client_animacion.h"

#include <SDL2pp/SDL2pp.hh>
#include <map>

class Explosion
{

private:
    std::shared_ptr<SDL2pp::Texture> texture; // Atributo que almacena la textura de la animacion

    Animation ex;
    Animation circulo;
    Animation elipse;
    Animation fuego;

    int movimientoFuego;

public:
    Explosion(std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::shared_ptr<SDL2pp::Texture> ex);

    void update();
    void render(SDL2pp::Renderer &renderer, float x, float y, float camaraLimiteIzquierdo, float camaraLimiteSuperior); // Renderiza el arma.
    bool animacion_completa();
};

#endif // EXPLOSION_H
