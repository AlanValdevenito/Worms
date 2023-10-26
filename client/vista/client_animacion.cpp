#include <SDL2pp/SDL2pp.hh>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "client_animacion.h"

Animation::Animation(SDL2pp::Texture &texture): texture(texture), currentFrame(0),
                                                numFrames(this->texture.GetHeight() / this->texture.GetWidth()),
                                                size(this->texture.GetWidth()), elapsed(0.0f) {
    assert(this->numFrames > 0);
    assert(this->size > 0);
}

void Animation::update(float dt) {
    this->elapsed += dt;
    // Comprueba si el frame deberia ser actualizado en base al tiempo transcurrido desde la ultima actualizacion
    while (this->elapsed > FRAME_RATE) {
        this->advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}

void Animation::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType) {
    renderer.Copy(
            texture,
            SDL2pp::Rect(0, (this->size) * this->currentFrame, this->size, this->size),
            dst,
            0.0,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
        );
}

void Animation::advanceFrame() {
    this->currentFrame += 1;
    // Aseguramos que la animacion sea ciclica, volviendo al primer frame si se alcanza el ultimo.
    this->currentFrame = this->currentFrame % this->numFrames; 
}
