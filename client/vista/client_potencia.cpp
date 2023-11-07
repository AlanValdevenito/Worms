#include "client_potencia.h"

#include <cmath>
#include <iostream>

#define POTENCIA_MAXIMA 16

Potencia::Potencia(SDL2pp::Texture &potencia): texture(potencia), currentFrame(0), 
                                              numFrames(this->texture.GetHeight() / this->texture.GetWidth()), 
                                              size(this->texture.GetWidth()) {}

void Potencia::update() {
    if ((this->currentFrame < POTENCIA_MAXIMA)) {
        this->currentFrame++; 
    }
}

void Potencia::reiniciar() {
    this->currentFrame = 0;
}

int Potencia::get_current_frame() {
    return this->currentFrame;
}

void Potencia::render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda, int angulo) {
    
    int radio = 15;

    for (int i = 0; i < this->currentFrame; i++) {

        renderer.Copy(
            texture,
            SDL2pp::Rect(0, (this->size) * i, this->size, this->size),
            SDL2pp::Rect(x + ((mirandoIzquierda ? -radio : radio) * cos(angulo * (M_PI / 180))), 
                         y - (radio * sin(angulo * (M_PI / 180))), this->size, this->size)
        );

        radio += 8;
    }
}