#include "client_mira.h"

#include <cmath>

#define ANCHO_SPRITE 32
#define ALTO_SPRITE 32

#define OFFSET_MIRA 50

Mira::Mira(): angulo(45) {
}

float Mira::calcular_angulo(float adyadente) {
    return tan(this->angulo * (M_PI / 180)) * adyadente;
}

void Mira::render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda) {
    SDL2pp::Texture texture(renderer, SDL2pp::Surface(DATA_PATH "/mira.png").SetColorKey(true, 0));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);

    int offset = OFFSET_MIRA;

    if (mirandoIzquierda) {
        offset = -OFFSET_MIRA;
    } 

    renderer.Copy(
            texture,
            SDL2pp::NullOpt,
            SDL2pp::Rect(x + offset, y - calcular_angulo(OFFSET_MIRA), 50, 50)
        );
}