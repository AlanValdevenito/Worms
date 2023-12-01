#ifndef ANIMACION_ATAQUE_AEREO_H
#define ANIMACION_ATAQUE_AEREO_H

#include <SDL2pp/SDL2pp.hh>

#include "client_apuntado.h"
#include "vista_arma.h"
#include "vista_misil.h"

#include <map>

class AnimacionAtaqueAereo: public Arma
{

private:
    std::map<int, std::unique_ptr<AnimacionMisil>> misiles;

public:
    AnimacionAtaqueAereo(SDL2pp::Renderer &renderer);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    void render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;
};

#endif // ANIMACION_ATAQUE_AEREO_H
