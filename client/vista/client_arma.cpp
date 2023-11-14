#include "client_arma.h"

#include <cmath>

// Inicializamos con la imagen "/wbaz.png" ya que su numero de frames es de 32.

// Si por ejemplo inicializamos con la imagen "/worm_walk.pg" su numero de frames seria 15 y luego al hacerle un update
// para cambiar la imagen por "wbaz.png" sucederia que solo se podrian renderizar los primeros 15 frames cuando en realidad esta imagen
// tiene 32 frames.

Arma::Arma(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/wbaz.png").SetColorKey(true, 0))), 
                                        mira(renderer),
                                        potencia(renderer),
                                        currentFrame(0), 
                                        numFrames(this->texture.GetHeight() / this->texture.GetWidth()),
                                        size(this->texture.GetWidth()), 
                                        animacionCompleta(false) {}


/******************** ACTUALIZACION Y RENDERIZADO ********************/

void Arma::update(int it) {

    if (not this->animacionCompleta) {
        this->currentFrame++;
        this->currentFrame = this->currentFrame % this->numFrames;
    }

    if ((not this->animacionCompleta) && (this->currentFrame == this->numFrames - 1) && (this->texturaDeApuntado != "/")) {
        this->animacionCompleta = true;

        SDL2pp::Surface surface(DATA_PATH + this->texturaDeApuntado);

        this->numFrames = surface.GetHeight() / surface.GetWidth();
        this->size = surface.GetWidth();
        this->texture.Update(SDL2pp::NullOpt, surface.SetColorKey(true, 0));

        this->currentFrame = this->numFrames / 2;

    } else if ((not this->animacionCompleta) && (this->currentFrame == this->numFrames - 1)) {
        this->animacionCompleta = true;
    }
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

/******************** ARMA ********************/

void Arma::equipar_arma(int tipo, std::string &texturaDeArma, std::string &texturaDeApuntado) {
    this->tipoDeArma = tipo;
    this->texturaDeApuntado = texturaDeApuntado;

    SDL2pp::Surface surface(DATA_PATH + texturaDeArma);

    this->numFrames = surface.GetHeight() / surface.GetWidth();
    this->size = surface.GetWidth();
    this->texture.Update(SDL2pp::NullOpt, surface.SetColorKey(true, 0));
}

int Arma::get_tipo() {
    return this->tipoDeArma;
}

/******************** ANGULO ********************/

void Arma::aumentar_angulo() {
    this->mira.aumentar_angulo();
    
    // Tengo 15 frames de 90º a 0º
    // Tengo 15 frames de 0º a 90º
    // Cada +6 grados aumento +1 el frame actual ya que 90 / 15 = 6
    if ((this->currentFrame < this->numFrames - 2) && (get_angulo() % 6 == 0)) {
        this->currentFrame++;
    }
}

void Arma::decrementar_angulo() {
    this->mira.decrementar_angulo();
    
    if ((this->currentFrame > 0) && (get_angulo() % 6 == 0))  {
        this->currentFrame--;
    }
}

int Arma::get_angulo() {
    return this->mira.get_angulo();
}

/******************** POTENCIA ********************/

void Arma::aumentar_potencia() {
    this->potencia.update();
}

int Arma::get_potencia() {
    return this->potencia.get_current_frame();
}

/******************** REINICIO DE LAS ANIMACIONES ********************/

void Arma::reiniciar() {
    this->animacionCompleta = false;
    this->currentFrame = 0;

    this->mira.reiniciar();
    this->potencia.reiniciar();
}

bool Arma::get_animacion_completa() {
    return this->animacionCompleta;
}
