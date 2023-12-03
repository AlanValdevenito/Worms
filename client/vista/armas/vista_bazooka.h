#ifndef ANIMACION_BAZOOKA_H
#define ANIMACION_BAZOOKA_H

#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "vista_arma.h"
#include "client_apuntado.h"
#include "animacion_humo.h"

class AnimacionBazooka: public AnimacionArma
{

private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas;

    Animacion movimiento;
    std::vector<AnimacionHumo> humo;
    AnimacionExplosion explosion;
    AnimacionApuntado apuntado;

    Sonido sonido;

    int angulo;
    int direccion;

public:
    AnimacionBazooka(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    void render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;
    void renderizar_humo(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void aumentar_angulo() override;
    void decrementar_angulo() override;
    int get_angulo() override;

    void aumentar_potencia() override;
    int get_potencia() override;
};

#endif // ANIMACION_BAZOOKA_H
