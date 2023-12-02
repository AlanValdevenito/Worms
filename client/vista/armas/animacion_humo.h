#ifndef ANIMACION_HUMO_H
#define ANIMACION_HUMO_H

#include <SDL2pp/SDL2pp.hh>
#include "client_animacion.h"

class AnimacionHumo
{

private:
    Animation animacion;

    int x;
    int y;

public:
    AnimacionHumo(std::shared_ptr<SDL2pp::Texture> textura, int x, int y);

    void render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
};

#endif // ANIMACION_HUMO_H
