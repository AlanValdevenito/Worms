#ifndef MIRA_H
#define MIRA_H

#include <SDL2pp/SDL2pp.hh>
#include "client_mira.h"

class Mira
{

private:

    int angulo;

public:
    Mira();

    // Renderiza la mira.
    void render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda);
    float calcular_angulo(float adyacente);
};

#endif // MIRA_H