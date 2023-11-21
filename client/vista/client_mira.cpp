#include "client_mira.h"

#include <cmath>

#define OFFSET 16

#define RADIO 176

Mira::Mira(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/mira.png").SetColorKey(true, 0))),
                                        size(this->texture.GetWidth()), 
                                        angulo(0) {}

void Mira::render(SDL2pp::Renderer &renderer, float x, float y, int direccion) {

    renderer.Copy(
        texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(x + OFFSET + ((direccion ? RADIO : -RADIO) * cos(this->angulo * (M_PI / 180))), 
                        y + OFFSET - (RADIO * sin(this->angulo * (M_PI / 180))), this->size, this->size)
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
