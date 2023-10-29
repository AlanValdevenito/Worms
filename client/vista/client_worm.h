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
    // Booleano que indica si el jugador se esta moviendo.
    bool moviendo;
    // Enteros que indican la posicion del Worm en pixeles.
    int x;
    int y;

public:
    Worm(SDL2pp::Texture &texture, int x, int y);

    // Actualiza el Worm en funcion del tiempo transcurrido.
    void update(float dt, float nuevoX, float nuevoY);
    // Renderiza el Worm.
    void render(SDL2pp::Renderer &renderer);
    // Actualiza los booleanos para indicar que el Worm se mueve a la derecha.
    void moveRigth();
    // Actualiza los booleanos para indicar que el Worm se mueve a la izquierda.
    void moveLeft();
    // Detiene el movimiendo del Worm actualizando el booleano.
    void stopMoving();
};

#endif // __WORM_H_
