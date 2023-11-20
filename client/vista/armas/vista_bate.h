#ifndef ANIMACION_BATE_DE_BASEBALL_H
#define ANIMACION_BATE_DE_BASEBALL_H

#include <SDL2pp/SDL2pp.hh>

#include "vista_arma.h"
#include "client_apuntado.h"

class AnimacionBateDeBaseball: public Arma 
{

private:
    Apuntado apuntado;

    int angulo;
    // Animation animacion;

public:
    AnimacionBateDeBaseball(SDL2pp::Renderer &renderer);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    void render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;

    void aumentar_angulo() override;
    void decrementar_angulo() override;
    int get_angulo() override;
};

#endif // ANIMACION_BATE_DE_BASEBALL_H