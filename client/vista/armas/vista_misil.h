#ifndef ANIMACION_MISIL_H
#define ANIMACION_MISIL_H

#include <SDL2pp/SDL2pp.hh>

#include "vista_arma.h"

class AnimacionMisil: public Arma
{

private:
    Animation movimiento;
    Explosion explosion;

    Sonido sonido;

public:
    AnimacionMisil(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    void render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;
};

#endif // ANIMACION_MISIL_H
