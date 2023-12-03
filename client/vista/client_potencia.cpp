#include "client_potencia.h"

#include <cmath>
#include <iostream>

#define POTENCIA_MAXIMA 16

AnimacionPotencia::AnimacionPotencia(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/potencia.png").SetColorKey(true, 0))), 
                                                currentFrame(0), 
                                                numFrames(this->texture.GetHeight() / this->texture.GetWidth()), 
                                                size(this->texture.GetWidth()) {}

void AnimacionPotencia::update() {
    if ((this->currentFrame < POTENCIA_MAXIMA)) {
        this->currentFrame++; 
    }
}

void AnimacionPotencia::render(SDL2pp::Renderer &renderer, float x, float y, int direccion, int angulo) {
    
    int radio = 15;

    for (int i = 0; i < this->currentFrame; i++) {

        renderer.Copy(
            this->texture,
            SDL2pp::Rect(0, (this->size) * i, this->size, this->size),
            SDL2pp::Rect(x + ((direccion ? radio : -radio) * cos(angulo * (M_PI / 180))), 
                         y - (radio * sin(angulo * (M_PI / 180))), this->size, this->size)
        );

        radio += 8;
    }
}

int AnimacionPotencia::get_current_frame() {
    return this->currentFrame;
}

void AnimacionPotencia::reiniciar() {
    this->currentFrame = 0;
}
