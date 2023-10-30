#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

Worm::Worm(SDL2pp::Texture &texture, float x, float y) : animacion(texture), mirandoIzquierda(false), x(x), y(y) {}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos. Esto les va a resultar muy util.

void Worm::update(int it, float nuevoX, float nuevoY)
{
 
    this->animacion.update(it);

    if (nuevoX < this->x)
    {
        this->mirandoIzquierda = true;
    
    } else if (nuevoX > this->x)
    {
        this->mirandoIzquierda = false;
    }

    this->x = nuevoX;
    this->y = nuevoY;
}

void Worm::render(SDL2pp::Renderer &renderer)
{
    SDL_RendererFlip flip = this->mirandoIzquierda ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    this->animacion.render(renderer, SDL2pp::Rect(x - 30, y - 55, ANCHO_SPRITE, ALTO_SPRITE), flip);
}
