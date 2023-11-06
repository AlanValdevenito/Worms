#include "client_arma.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

#include <cmath>

Arma::Arma(SDL2pp::Texture &arma): texture(arma), currentFrame(0), animacionCompleta(false) {}

void Arma::update() {

    if (not this->animacionCompleta) {
        this->currentFrame++;
        this->currentFrame = this->currentFrame % 10;
    }

    if (this->currentFrame == 9) {
        this->animacionCompleta = true;
    }
}

void Arma::reiniciar() {
    this->animacionCompleta = false;
    this->currentFrame = 0;
}

bool Arma::get_animacion_completa() {
    return this->animacionCompleta;
}

void Arma::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType) {

    std::cout << this->currentFrame << std::endl;

    renderer.Copy(
        texture,
        SDL2pp::Rect(0, (ANCHO_SPRITE) * this->currentFrame, ANCHO_SPRITE, ANCHO_SPRITE),
        dst,
        0.0,                // don't rotate
        SDL2pp::NullOpt,    // rotation center - not needed
        flipType
    );

}