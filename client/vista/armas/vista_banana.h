#ifndef ANIMACION_BANANA_H
#define ANIMACION_BANANA_H

#include <SDL2pp/SDL2pp.hh>

#include "vista_arma.h"
#include "client_apuntado.h"

class AnimacionBanana: public Arma
{

private:
    Animation movimiento;
    Explosion explosion;
    Apuntado apuntado;

    Sonido sonido;

    int angulo;
    int tiempo;

public:
    AnimacionBanana(SDL2pp::Renderer &renderer);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    
    void render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;
    void renderizar_tiempo(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void set_tiempo(int tiempoElegido) override;
    int get_tiempo() override;

    void aumentar_angulo() override;
    void decrementar_angulo() override;
    int get_angulo() override;

    void aumentar_potencia() override;
    int get_potencia() override;
};

#endif // ANIMACION_BANANA_H
