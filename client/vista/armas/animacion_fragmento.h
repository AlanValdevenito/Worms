#ifndef ANIMACION_FRAGMENTO_H
#define ANIMACION_FRAGMENTO_H

#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "animacion_arma.h"
#include "client_apuntado.h"
#include "animacion_humo.h"

class AnimacionFragmento: public AnimacionArma
{

private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas;

    Animacion movimiento;
    std::vector<AnimacionHumo> humo;
    AnimacionExplosion explosion;

    Sonido sonido;

    int angulo;

public:
    AnimacionFragmento(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    
    void render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;
    void renderizar_humo(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
};

#endif // ANIMACION_FRAGMENTO_H