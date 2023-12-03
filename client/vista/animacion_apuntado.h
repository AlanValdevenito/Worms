#ifndef APUNTADO_H
#define APUNTADO_H

#include <SDL2pp/SDL2pp.hh>

#include "animacion_mira.h"
#include "animacion_potencia.h"

class AnimacionApuntado
{

private:
    std::shared_ptr<SDL2pp::Texture> texture; // Atributo que almacena la textura de la animacion

    AnimacionMira mira;
    AnimacionPotencia potencia;

    int tipoDeArma;

    int numFrames;
    int currentFrame;
    int size; // Entero que almacena el tamaño de cada frame (altura y ancho).

public:
    AnimacionApuntado(SDL2pp::Renderer &renderer);
    AnimacionApuntado(SDL2pp::Renderer &renderer, std::shared_ptr<SDL2pp::Texture> textura);

    void aumentar_potencia();
    void aumentar_angulo();
    void decrementar_angulo();

    void render(SDL2pp::Renderer &renderer, float x, float y, int direccion); // Renderiza el arma.

    int get_angulo();
    int get_potencia();
};

#endif // APUNTADO_H
