#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include <map>

#include "animacion.h"
#include "constantes.h"
#include "sonido.h"

#include "animacion_bate.h"
#include "animacion_granada_verde.h"
#include "animacion_bazooka.h"
#include "animacion_banana.h"
#include "animacion_granada_santa.h"
#include "animacion_dinamita.h"
#include "animacion_ataque_aereo.h"
#include "animacion_granada_roja.h"
#include "animacion_mortero.h"

class AnimacionWorm
{

private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas;
    std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos;

    Animacion animacion;
    std::unique_ptr<AnimacionArma> arma;
    std::shared_ptr<Sonido> sonido;

    int estado;

    int tipoDeArma;

    float x;
    float y;
    int vida;
    int direccion; // 0 izquierda y 1 derecha
    int angulo;

    bool turno;
    int numeroColor;

    SDL2pp::Color &color;

public:
    bool camara;

    AnimacionWorm(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos, SDL2pp::Color &color, int numeroColor, float x, float y, int vida, int direccion);

    void update(int it, float nuevoX, float nuevoY, int vida, int direccion, int angulo,  bool turno); // Actualiza el Worm en funcion del tiempo transcurrido.
    void update_estado(SDL2pp::Renderer &renderer, int nuevoEstado, int arma = 0);

    void equipar_arma(SDL2pp::Renderer &renderer, int tipoDeArma);

    void render(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void render_arma(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void render_vida(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    int get_tipo_de_arma();

    void update_proyectil(SDL2pp::Renderer &renderer, int id, float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion, int nuevoFlag, int nuevoTiempo);
    void set_tiempo(int tiempo);
    int get_tiempo();

    void aumentar_angulo();
    void decrementar_angulo();
    int get_angulo();

    void aumentar_potencia();
    int get_potencia();

    float get_x();
    float get_y();
    int get_vida();
    int get_estado();
    int get_color();
    bool get_turno();

    void set_turno(bool nuevoTurno);
    void set_camara(bool nuevaCamara);
};

#endif // __WORM_H_
