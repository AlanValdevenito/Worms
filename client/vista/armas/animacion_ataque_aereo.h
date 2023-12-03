#ifndef ANIMACION_ATAQUE_AEREO_H
#define ANIMACION_ATAQUE_AEREO_H

#include <SDL2pp/SDL2pp.hh>

#include "animacion_apuntado.h"
#include "animacion_arma.h"
#include "animacion_misil.h"

#include <map>

class AnimacionAtaqueAereo: public AnimacionArma
{

private:
    std::map<int, std::unique_ptr<AnimacionMisil>> misiles;

public:
    AnimacionAtaqueAereo(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    void render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;
};

#endif // ANIMACION_ATAQUE_AEREO_H
