#ifndef MIRA_H
#define MIRA_H

#include <SDL2pp/SDL2pp.hh>

class Mira
{

private:

    int angulo;

public:
    Mira();

    void render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda);
    void aumentar_angulo();
    void decrementar_angulo();
};

#endif // MIRA_H