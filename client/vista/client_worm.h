#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "client_animacion.h"
#include "client_arma.h"
#include "client_mira.h"
#include "client_potencia.h"
#include <map>

class Worm
{

private:
    // Objeto del tipo Animacion.
    // Se usa para almacenar y gestionar la animacion del Worm.
    Animation animacion;

    Arma arma;
    Mira mira;
    Potencia potencia;
    std::map<int, SDL2pp::Color> &colores;

    bool armaEquipada;
    // Booleano que indica si el jugador activo la mira.
    bool miraActivada;
    // Booleano que indica si el jugador esta mirando hacia la izquierda.
    bool mirandoIzquierda;
    // Enteros que indican la posicion del Worm en pixeles.
    float x;
    float y;
    int vida;
    int color;

public:

    Worm(SDL2pp::Texture &texture, SDL2pp::Texture &arma, SDL2pp::Texture &potencia, std::map<int, SDL2pp::Color> &colores, float x, float y, int vida, int color);

    // Actualiza el Worm en funcion del tiempo transcurrido.
    void update(int it, float nuevoX, float nuevoY, int vida);
    // Renderiza el Worm.
    void render(SDL2pp::Renderer &renderer);
    void render_vida(SDL2pp::Renderer &renderer);

    void mirar_derecha();
    void mirar_izquierda();

    void equipar_arma();
    void desequipar_arma();
    bool arma_equipada();
    void aumentar_angulo();
    void decrementar_angulo();

    void aumentar_potencia();
    int get_potencia();
    int get_vida();
    int get_angulo();
};

#endif // __WORM_H_
