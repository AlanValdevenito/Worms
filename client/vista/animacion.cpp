#include <SDL2pp/SDL2pp.hh>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "animacion.h"

Animacion::Animacion(std::shared_ptr<SDL2pp::Texture> textura, bool repetirAnimacion): textura(textura),
                                                                                       currentFrame(0),
                                                                                       numFrames(this->textura->GetHeight() / this->textura->GetWidth()),
                                                                                       size(this->textura->GetWidth()), repetirAnimacion(repetirAnimacion) {
    assert(this->numFrames > 0);
    assert(this->size > 0);
}

void Animacion::update(int it) {

    if (this->repetirAnimacion) {
            this->currentFrame = it;
            this->currentFrame = this->currentFrame % this->numFrames; 
    
    } else if (this->currentFrame < this->numFrames - 1) {
        this->currentFrame++;
    }
}

void Animacion::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType, int angulo) {
    renderer.Copy(
            *textura,
            SDL2pp::Rect(0, (this->size) * this->currentFrame, this->size, this->size),
            dst,
            angulo,
            SDL2pp::NullOpt,
            flipType
        );
}

void Animacion::cambiar(std::shared_ptr<SDL2pp::Texture> nuevaTextura) {
    this->textura = nuevaTextura;
    this->currentFrame = 0;
    this->numFrames = this->textura->GetHeight() / this->textura->GetWidth();
    this->size = this->textura->GetWidth();
    this->repetirAnimacion = true;
}

void Animacion::no_repetir_animacion() {
    this->repetirAnimacion = false;
}

bool Animacion::completa() {
    return (this->currentFrame == this->numFrames - 1);
}

void Animacion::set_current_frame(int nuevoCurrentFrame) {
    this->currentFrame = nuevoCurrentFrame;
}
