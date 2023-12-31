#ifndef ANIMACION_GRANADA_ROJA_H
#define ANIMACION_GRANADA_ROJA_H

#include <SDL2pp/SDL2pp.hh>

#include "animacion_arma.h"
#include "animacion_apuntado.h"
#include "animacion_fragmento.h"
#include <map>

class AnimacionGranadaRoja: public AnimacionArma
{

private:
    std::map<int, std::unique_ptr<AnimacionFragmento>> fragmentos;

    Animacion movimiento;
    AnimacionExplosion explosion;
    AnimacionApuntado apuntado;

    Sonido sonido;

    int angulo;
    int tiempo;

public:
    AnimacionGranadaRoja(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos);

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

#endif // ANIMACION_GRANADA_ROJA_H
