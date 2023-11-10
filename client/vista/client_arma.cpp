#include "client_arma.h"

#include <cmath>

Arma::Arma(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/wbsblnk.png").SetColorKey(true, 0))), 
                                        mira(renderer),
                                        potencia(renderer),
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

void Arma::equipar_arma(int tipo, std::string &ruta) {
    this->tipoDeArma = tipo;
    this->texture.Update(SDL2pp::NullOpt, SDL2pp::Surface(DATA_PATH + ruta).SetColorKey(true, 0));
}

int Arma::get_tipo() {
    return this->tipoDeArma;
}

void Arma::reiniciar() {
    this->animacionCompleta = false;
    this->currentFrame = 0;

    this->mira.reiniciar();
    this->potencia.reiniciar();
}

bool Arma::get_animacion_completa() {
    return this->animacionCompleta;
}

void Arma::render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda) {

    SDL_RendererFlip flipType = mirandoIzquierda ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    renderer.Copy(
        this->texture,
        SDL2pp::Rect(0, (this->size) * this->currentFrame, this->size, this->size),
        SDL2pp::Rect(x, y, this->size, this->size),
        0.0,                // don't rotate
        SDL2pp::NullOpt,    // rotation center - not needed
        flipType
    );

    this->mira.render(renderer, x, y, mirandoIzquierda);
    this->potencia.render(renderer, x, y, mirandoIzquierda, this->mira.get_angulo());
}

void Arma::aumentar_angulo() {
    this->mira.aumentar_angulo();
}

void Arma::decrementar_angulo() {
    this->mira.decrementar_angulo();
}

void Arma::aumentar_potencia() {
    this->potencia.update();
}

int Arma::get_potencia() {
    return this->potencia.get_current_frame();
}

int Arma::get_angulo() {
    return this->mira.get_angulo();
}
