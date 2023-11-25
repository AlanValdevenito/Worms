#include "client_apuntado.h"

#include <cmath>

Apuntado::Apuntado(SDL2pp::Renderer &renderer, std::shared_ptr<SDL2pp::Texture> textura): texture(textura), 
                                        mira(renderer),
                                        potencia(renderer),
                                        numFrames(this->texture->GetHeight() / this->texture->GetWidth()),
                                        currentFrame(this->numFrames / 2), 
                                        size(this->texture->GetWidth()) {}


/******************** ACTUALIZACION Y RENDERIZADO ********************/

void Apuntado::aumentar_potencia() {
    this->potencia.update();
}

void Apuntado::aumentar_angulo() {
    this->mira.aumentar_angulo();
    
    if ((this->currentFrame < this->numFrames - 2) && (get_angulo() % 6 == 0)) {
        this->currentFrame++;
    }
}

void Apuntado::decrementar_angulo() {
    this->mira.decrementar_angulo();
    
    if ((this->currentFrame > 0) && (get_angulo() % 6 == 0))  {
        this->currentFrame--;
    }
}

void Apuntado::render(SDL2pp::Renderer &renderer, float x, float y, int direccion) {

    SDL_RendererFlip flipType = direccion ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    renderer.Copy(
        *this->texture,
        SDL2pp::Rect(0, (this->size) * this->currentFrame, this->size, this->size),
        SDL2pp::Rect(x, y, this->size, this->size),
        0.0,                // don't rotate
        SDL2pp::NullOpt,    // rotation center - not needed
        flipType
    );

    this->mira.render(renderer, x, y, direccion);
    this->potencia.render(renderer, x, y, direccion, this->mira.get_angulo());
}

/******************** GETTERS ********************/

int Apuntado::get_angulo() {
    return this->mira.get_angulo();
}

int Apuntado::get_potencia() {
    return this->potencia.get_current_frame();
}
