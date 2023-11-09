#ifndef _GRANADA_H
#define _GRANADA_H

#include <SDL2pp/SDL2pp.hh>

class Granada
{

private:
    // Atributo que almacena la textura de la animacion
    // Es una referencia para que esta pueda ser cambiada en cualquier momento segun el evento que este ocurriendo
    SDL2pp::Texture texture;
    // Entero que almacena el tamaño de cada frame (altura y acho).
    int size;

    // Enteros que indican la posicion del Worm en pixeles.
    float x;
    float y;

public:
    Granada(SDL2pp::Renderer &renderer, float x, float y);

    // Renderiza la potencia.
    void render(SDL2pp::Renderer &renderer);
    void update(float nuevoX, float nuevoY);
};

#endif // _GRANADA_H
