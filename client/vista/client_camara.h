#ifndef CAMARA_H
#define CAMARA_H

#include <SDL2pp/SDL2pp.hh>

#include "client_worm.h"

class Camara
{

private:
    // Posicion del Worm a seguir
    // Representa el centro de la camara
    float x,y;
    // Dimensiones de la camara.
    float ancho, alto;

public:
    Camara(float ventanaAncho, float ventanaAlto);
    void seguirWorm(Worm &worm); // Actualiza la posicion de la camara para seguir al Worm
    bool comprobarRenderizado(float objetoX, float objetoY, float objetoAncho, float objetoAlto);

    void update();
};

#endif // CAMARA_H