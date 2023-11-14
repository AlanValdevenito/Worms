#ifndef ARMA_H
#define ARMA_H

#include <SDL2pp/SDL2pp.hh>

#include "client_mira.h"
#include "client_potencia.h"

class Arma
{

private:
    SDL2pp::Texture texture; // Atributo que almacena la textura de la animacion

    Mira mira;
    Potencia potencia;

    int tipoDeArma;

    int currentFrame;
    int numFrames;
    int size; // Entero que almacena el tamaño de cada frame (altura y ancho).

    bool animacionCompleta;
    std::string texturaDeApuntado;

public:
    Arma(SDL2pp::Renderer &renderer);

    void update(int it); // Actualiza la animacion. 
    void render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda); // Renderiza el arma.

    void equipar_arma(int tipo, std::string &texturaDeArma, std::string &texturaDeApuntado);
    int get_tipo();

    void aumentar_angulo();
    void decrementar_angulo();
    int get_angulo();

    void aumentar_potencia();
    int get_potencia();

    void reiniciar();
    bool get_animacion_completa();
};

#endif // ARMA_H