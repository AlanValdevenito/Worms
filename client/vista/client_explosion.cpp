#include "client_explosion.h"

Explosion::Explosion(SDL2pp::Renderer &renderer): biff(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0)), false),
                                                  circulo(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/circle50.png").SetColorKey(true, 0)), false),
                                                  elipse(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/elipse50.png").SetColorKey(true, 0)), false),
                                                  fuego(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/flame1.png").SetColorKey(true, 0)), false),
                                                  movimientoFuego(0) {}

void Explosion::update() {
    this->fuego.update(1);
    this->circulo.update(1);
    this->elipse.update(1);
    this->biff.update(1);
}

void Explosion::render(SDL2pp::Renderer &renderer, float x, float y, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (not this->fuego.completa()) {
        this->fuego.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo - 2 - movimientoFuego, y - 30 - camaraLimiteSuperior - 20 + movimientoFuego, 60, 60), flip);
        this->fuego.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo + 2 + movimientoFuego, y - 30 - camaraLimiteSuperior - 20 + movimientoFuego, 60, 60), flip);

        this->fuego.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo - 20 - movimientoFuego, y - 30 - camaraLimiteSuperior + movimientoFuego, 60, 60), flip);
        this->fuego.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo + 20 + movimientoFuego, y - 30 - camaraLimiteSuperior + movimientoFuego, 60, 60), flip);
    }
 
    if (not this->circulo.completa()) {
        this->circulo.render(renderer, SDL2pp::Rect(x - 50 - camaraLimiteIzquierdo, y - 50 - camaraLimiteSuperior, 100, 100), flip);
    }

    if (not this->elipse.completa()) {
        this->elipse.render(renderer, SDL2pp::Rect(x - 75 - camaraLimiteIzquierdo, y - 75 - camaraLimiteSuperior, 150, 150), flip);
    }

    if (not this->biff.completa()) {
        this->biff.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo, y - 30 - camaraLimiteSuperior, 60, 60), flip);
    }
    
    movimientoFuego += 1;
}

bool Explosion::animacion_completa() {
    return (this->fuego.completa() && this->circulo.completa() && this->elipse.completa() && this->biff.completa());
}
