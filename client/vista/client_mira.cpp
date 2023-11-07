#include "client_mira.h"

#include <cmath>

#define ANCHO_SPRITE 31
#define ALTO_SPRITE 31

#define X_OFFSET_MIRA 176
#define Y_OFFSET_MIRA 15

#define RADIO 176

Mira::Mira(): angulo(0) {
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

float Mira::calcular_opuesto(float adyadente) {
    return adyadente * tan(this->angulo * (M_PI / 180));
}

float Mira::calcular_adyacente(float opuesto) {
    return opuesto / tan(this->angulo * (M_PI / 180));
}

void Mira::render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda) {
    SDL2pp::Texture texture(renderer, SDL2pp::Surface(DATA_PATH "/mira.png").SetColorKey(true, 0));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);

    renderer.Copy(
            texture,
            SDL2pp::NullOpt,
            SDL2pp::Rect(x + ((mirandoIzquierda ? -RADIO : RADIO) * cos(this->angulo * (M_PI / 180))), y - (RADIO * sin(this->angulo * (M_PI / 180))), ANCHO_SPRITE, ALTO_SPRITE)
        );
}