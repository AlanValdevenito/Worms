#ifndef ANIMACION_FRAGMENTO_H
#define ANIMACION_FRAGMENTO_H

#include <SDL2pp/SDL2pp.hh>

#include "vista_arma.h"
#include "client_apuntado.h"

class AnimacionFragmento: public Arma
{

private:
    Animation movimiento;
    Explosion explosion;

    Sonido sonido;

    int angulo;

public:
    AnimacionFragmento(SDL2pp::Renderer &renderer, std::shared_ptr<SDL2pp::Chunk> sonido);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    
    void render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;
};

#endif // ANIMACION_FRAGMENTO_H