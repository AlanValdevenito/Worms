#include "client_mira.h"

#include <cmath>

#define ANCHO_SPRITE 31
#define ALTO_SPRITE 31

#define OFFSET 16

#define RADIO 176

Mira::Mira(): angulo(0) {
}

void Mira::render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda) {
    SDL2pp::Texture texture(renderer, SDL2pp::Surface(DATA_PATH "/mira.png").SetColorKey(true, 0));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);

    renderer.Copy(
        texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(x + ((mirandoIzquierda ? -RADIO : RADIO) * cos(this->angulo * (M_PI / 180))), 
                        y + OFFSET - (RADIO * sin(this->angulo * (M_PI / 180))), ANCHO_SPRITE, ALTO_SPRITE)
    );
}

void Mira::aumentar_angulo() {
    if(angulo < 90) {
        this->angulo++;
    }
}

void Mira::decrementar_angulo() {
    if(angulo > -90) {
        this->angulo--;
    }
}

int Mira::get_angulo() {
    return this->angulo;
}

void Mira::reiniciar() {
    this->angulo = 0;
}
