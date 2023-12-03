#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "animacion.h"

#include <SDL2pp/SDL2pp.hh>
#include <map>

class AnimacionExplosion
{

private:
    std::shared_ptr<SDL2pp::Texture> texture; // Atributo que almacena la textura de la animacion

    Animacion ex;
    Animacion circulo;
    Animacion elipse;
    Animacion fuego;

    int movimientoFuego;

public:
    AnimacionExplosion(std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::shared_ptr<SDL2pp::Texture> ex);

    void update();
    void render(SDL2pp::Renderer &renderer, float x, float y, float camaraLimiteIzquierdo, float camaraLimiteSuperior); // Renderiza el arma.
    bool animacion_completa();
};

#endif // EXPLOSION_H
