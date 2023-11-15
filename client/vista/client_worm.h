#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "client_animacion.h"
#include "client_arma.h"
#include <map>

#include "yaml-cpp/yaml.h"

class Worm
{

private:
    Animation animacion;
    Arma arma;

    bool armaEquipada;
    bool mirandoIzquierda;

    float x;
    float y;
    int vida;

    SDL2pp::Color &color;
    bool turno;

    YAML::Node configuraciones;

public:
    Worm(SDL2pp::Renderer &renderer, SDL2pp::Color &color, float x, float y, int vida);

    void update(int it, float nuevoX, float nuevoY, int vida); // Actualiza el Worm en funcion del tiempo transcurrido.

    void render(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void render_vida(SDL2pp::Renderer &renderer,float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void cambiar_animacion(std::string &ruta);

    void cambiar_turno();
    void turno_actual();

    void mirar_derecha();
    void mirar_izquierda();

    void equipar_arma(int tipo);
    void desequipar_arma();
    int get_tipo_de_arma();
    bool arma_equipada();

    void aumentar_angulo();
    void decrementar_angulo();
    int get_angulo();

    void aumentar_potencia();
    int get_potencia();

    float get_x();
    float get_y();
    int get_vida();

    void set_x(float nuevoX);
};

#endif // __WORM_H_
