#ifndef ARMA_H
#define ARMA_H

#include <SDL2pp/SDL2pp.hh>

#include "client_mira.h"
#include "client_potencia.h"

class Arma
{

private:
    // Atributo que almacena la textura de la animacion
    // Es una referencia para que esta pueda ser cambiada en cualquier momento segun el evento que este ocurriendo
    SDL2pp::Texture texture;

    Mira mira;
    Potencia potencia;

    int tipoDeArma;
    int currentFrame;
    int numFrames;
    int size;
    bool animacionCompleta;

public:
    Arma(SDL2pp::Renderer &renderer);

    // Actualiza la animacion. 
    void update();

     // Renderiza la arma.
    void render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda);

    void reiniciar();

    void equipar_arma(int tipo, std::string &ruta);

    bool get_animacion_completa();
    int get_tipo();

    void aumentar_angulo();
    void decrementar_angulo();

    void aumentar_potencia();
    int get_potencia();
    int get_angulo();
};

#endif // ARMA_H