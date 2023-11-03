#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

#define OFFSET_X -30
#define OFFSET_Y -55

Worm::Worm(SDL2pp::Texture &texture, float x, float y) : animacion(texture), mira(Mira()), miraActivada(false), mirandoIzquierda(true), x(x), y(y) {}

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

void Worm::activar_mira() {
    this->miraActivada = true;
}

void Worm::desactivar_mira() {
    this->miraActivada = false;
}

bool Worm::get_mira() {
    return this->miraActivada;
}

void Worm::render(SDL2pp::Renderer &renderer)
{
    SDL_RendererFlip flip = this->mirandoIzquierda ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    this->animacion.render(renderer, SDL2pp::Rect(x + OFFSET_X, y + OFFSET_Y, ANCHO_SPRITE, ALTO_SPRITE), flip);
 
    if (this->miraActivada) {
        this->mira.render(renderer, x + OFFSET_X, y + OFFSET_Y, this->mirandoIzquierda);
    } 

}
