#ifndef MIRA_H
#define MIRA_H

#include <SDL2pp/SDL2pp.hh>

class Mira
{

private:

    int angulo;

public:
    Mira();

    // Renderiza la mira.
    void render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda);

    void aumentar_angulo();
    void decrementar_angulo();

    float calcular_opuesto(float adyacente);
    float calcular_adyacente(float opuesto);
};

#endif // MIRA_H