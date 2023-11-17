#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "client_animacion.h"
#include "client_proyectil.h"
#include "client_apuntado.h"
#include <map>

#include "yaml-cpp/yaml.h"

const int MOVIENDOSE = 0;
const int EQUIPANDO_ARMA = 1;
const int APUNTANDO = 2;

const int BATE = 7;
const int GRANADA_VERDE = 2;
const int BAZOOKA = 0;
const int BANANA = 4;
const int GRANADA_SANTA = 5;
const int DINAMITA = 6;
const int TELETRANSPORTACION = 9;

class Worm
{

private:
    Animation animacion;
    Apuntado apuntado;
    AnimacionProyectil proyectil;

    int estado;

    bool apuntadoActivado;
    int tipoDeArma;

    float x;
    float y;
    int vida;

    bool turno;
    bool mirandoIzquierda;

    SDL2pp::Color &color;
    YAML::Node configuraciones;

public:
    Worm(SDL2pp::Renderer &renderer, SDL2pp::Color &color, float x, float y, int vida);

    void update(int it, float nuevoX, float nuevoY, int vida); // Actualiza el Worm en funcion del tiempo transcurrido.
    void update_estado(SDL2pp::Renderer &renderer, int nuevoEstado, int arma = -1);

    void render(SDL2pp::Renderer &renderer, Camara &camara, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void render_vida(SDL2pp::Renderer &renderer,float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void desactivar_turno();
    void activar_turno();

    void mirar_derecha();
    void mirar_izquierda();

    int get_tipo_de_arma();

    void update_proyectil(float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion);
    void set_flag_proyectil(int flag);
    int get_flag_proyectil();
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
};

#endif // __WORM_H_
