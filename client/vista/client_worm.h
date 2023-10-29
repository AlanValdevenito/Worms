#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "client_animacion.h"

class Worm
{

private:
    // Objeto del tipo Animacion.
    // Se usa para almacenar y gestionar la animacion del Worm.
    Animation animacion;

    // Booleano que indica si el jugador esta mirando hacia la izquierda.
    bool mirandoIzquierda;
    // Enteros que indican la posicion del Worm en pixeles.
    float x;
    float y;

public:
    Worm(SDL2pp::Texture &texture, float x, float y);

    // Actualiza el Worm en funcion del tiempo transcurrido.
    void update(float dt, float nuevoX, float nuevoY);
    // Renderiza el Worm.
    void render(SDL2pp::Renderer &renderer);
};

#endif // __WORM_H_
