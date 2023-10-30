#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

Worm::Worm(SDL2pp::Texture &texture, float x, float y) : animacion(texture), mirandoIzquierda(false), x(x), y(y) {}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos. Esto les va a resultar muy util.

void Worm::update(int it, float nuevoX, float nuevoY)
{
 
    animacion.update(it);

    if (nuevoX < x)
    {
        mirandoIzquierda = true;
    
    } else if (nuevoX >= x)
    {
        mirandoIzquierda = false;
    }

    x = nuevoX;
    y = nuevoY;
}

void Worm::render(SDL2pp::Renderer &renderer)
{
    SDL_RendererFlip flip = mirandoIzquierda ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    animacion.render(renderer, SDL2pp::Rect(x - 30, y - 55, ANCHO_SPRITE, ALTO_SPRITE), flip);
}
