#include "client_mira.h"

#include <cmath>

#define RADIO 140

AnimacionMira::AnimacionMira(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/crshairr.png").SetColorKey(true, 0))),
                                        size(this->texture.GetWidth()), 
                                        angulo(0) {}

void AnimacionMira::render(SDL2pp::Renderer &renderer, float x, float y, int direccion) {

    renderer.Copy(
        texture,
        SDL2pp::Rect(0, (this->size) * 0, this->size, this->size),
        SDL2pp::Rect(x + ((direccion ? RADIO : -RADIO) * cos(this->angulo * (M_PI / 180))), 
                        y + 3 - (RADIO * sin(this->angulo * (M_PI / 180))), this->size, this->size)
    );
}

void AnimacionMira::aumentar_angulo() {
    if(angulo < 90) {
        this->angulo++;
    }
}

void AnimacionMira::decrementar_angulo() {
    if(angulo > -90) {
        this->angulo--;
    }
}

int AnimacionMira::get_angulo() {
    return this->angulo;
}

void AnimacionMira::reiniciar() {
    this->angulo = 0;
}
