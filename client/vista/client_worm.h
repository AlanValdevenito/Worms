#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "client_animacion.h"
#include "client_mira.h"

class Worm
{

private:
    // Objeto del tipo Animacion.
    // Se usa para almacenar y gestionar la animacion del Worm.
    Animation animacion;

    Mira mira;

    // Booleano que indica si el jugador activo la mira.
    bool miraActivada;
    // Booleano que indica si el jugador esta mirando hacia la izquierda.
    bool mirandoIzquierda;
    // Enteros que indican la posicion del Worm en pixeles.
    float x;
    float y;

public:

    Worm(SDL2pp::Texture &texture, float x, float y);

    // Actualiza el Worm en funcion del tiempo transcurrido.
    void update(int it, float nuevoX, float nuevoY);
    // Renderiza el Worm.
    void render(SDL2pp::Renderer &renderer);

    void activar_mira();
    void desactivar_mira();
    bool get_mira();
    
};

#endif // __WORM_H_
