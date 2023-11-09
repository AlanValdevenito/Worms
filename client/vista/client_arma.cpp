#include "client_arma.h"

#include <cmath>

Arma::Arma(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/wbsblnk.png").SetColorKey(true, 0))), 
                                        currentFrame(0), 
                                        numFrames(this->texture.GetHeight() / this->texture.GetWidth()),
                                        size(this->texture.GetWidth()), 
                                        animacionCompleta(false) {}

void Arma::update() {

    if (not this->animacionCompleta) {
        this->currentFrame++;
        this->currentFrame = this->currentFrame % 10;
    }

    if (this->currentFrame == this->numFrames - 1) {
        this->animacionCompleta = true;
    }
}

void Arma::cambiar_arma(int tipo, std::string &ruta) {
    this->tipoDeArma = tipo;
    this->texture.Update(SDL2pp::NullOpt, SDL2pp::Surface(DATA_PATH + ruta).SetColorKey(true, 0));
}

int Arma::get_tipo() {
    return this->tipoDeArma;
}

void Arma::reiniciar() {
    this->animacionCompleta = false;
    this->currentFrame = 0;
}

bool Arma::get_animacion_completa() {
    return this->animacionCompleta;
}

void Arma::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType) {

    renderer.Copy(
        texture,
        SDL2pp::Rect(0, (this->size) * this->currentFrame, this->size, this->size),
        dst,
        0.0,                // don't rotate
        SDL2pp::NullOpt,    // rotation center - not needed
        flipType
    );

}