#ifndef _CAMARA_H
#define _CAMARA_H

#include "animacion_worm.h"
#include <map>

class Camara
{

private:
    // Posicion del Worm a seguir
    // Representa el centro de la camara
    float x,y;
    // Dimensiones de la camara.
    float ancho, alto;

public:
    bool moverCamara;
    Camara(float ventanaAncho, float ventanaAlto);

    void seguirWorm(std::map<int, AnimacionWorm*> &worms);
    void seguir(float nuevoX, float nuevoY); // Actualiza la posicion de la camara para seguir al Worm
    void mover(float moverX, float moverY);

    bool comprobarRenderizado(float objetoX, float objetoY, float objetoAncho, float objetoAlto);
    float getLimiteDerecho();
    float getLimiteIzquierdo();
    float getLimiteSuperior();
    float getLimiteInferior();
    float getCentroX();

    void setDimensiones(float ventanaAncho, float ventanaAlto);
    void setMoverCamara(bool nuevoMover);
};

#endif // _CAMARA_H
