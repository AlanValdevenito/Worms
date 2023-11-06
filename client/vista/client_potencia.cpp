#include "client_potencia.h"

#include <cmath>

Potencia::Potencia(SDL2pp::Texture &potencia): texture(potencia), currentFrame(0), 
                                              numFrames(this->texture.GetHeight() / this->texture.GetWidth()), 
                                              size(this->texture.GetWidth()), angulo(45) {}

void Potencia::update() {
    this->currentFrame++;
    this->currentFrame = this->currentFrame % this->numFrames; 
}

void Potencia::reiniciar() {
    this->currentFrame = 0;
}

int Potencia::get_current_frame() {
    return this->currentFrame;
}

float Potencia::calcular_angulo(float adyadente) {
    return tan(this->angulo * (M_PI / 180)) * adyadente;
}

void Potencia::render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda) {
    
    int offset = 15;

    for (int i = 0; i < this->currentFrame; i++) {

        renderer.Copy(
            texture,
            SDL2pp::Rect(0, (this->size) * i, this->size, this->size),
            SDL2pp::Rect(x + (mirandoIzquierda ? (offset * -1) : offset), y, this->size, this->size)
        );

        offset += 8;
    }
}