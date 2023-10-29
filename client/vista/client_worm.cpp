#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

Worm::Worm(SDL2pp::Texture &texture, int x, int y) : animacion(texture), mirandoIzquierda(false), moviendo(false), x(x), y(y) {}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos. Esto les va a resultar muy util.

void Worm::update(float dt, float nuevoX, float nuevoY)
{
    if (moviendo)
    {
        animacion.update(dt);

        if (mirandoIzquierda)
        {
            x -= nuevoX;
        }
        else
        {
            x += nuevoX;
        }
    }

    y += nuevoY;
}

void Worm::render(SDL2pp::Renderer &renderer)
{
    SDL_RendererFlip flip = mirandoIzquierda ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    animacion.render(renderer, SDL2pp::Rect(x, y - 42, ANCHO_SPRITE, ALTO_SPRITE), flip);
}

void Worm::moveRigth()
{
    moviendo = true;
    mirandoIzquierda = false;
}

void Worm::moveLeft()
{
    moviendo = true;
    mirandoIzquierda = true;
}

void Worm::stopMoving()
{
    moviendo = false;
}
