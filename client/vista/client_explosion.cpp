#include "client_explosion.h"

Explosion::Explosion(SDL2pp::Renderer &renderer): biff(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0)), false),
                                                  circulo(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/circle50.png").SetColorKey(true, 0)), false),
                                                  elipse(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/elipse50.png").SetColorKey(true, 0)), false) {}

void Explosion::update() {
    this->circulo.update(1);
    this->elipse.update(1);
    this->biff.update(1);
}

void Explosion::render(SDL2pp::Renderer &renderer, float x, float y, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    this->circulo.render(renderer, SDL2pp::Rect(x - 50 - camaraLimiteIzquierdo, y - 50 - camaraLimiteSuperior, 100, 100), flip);
    this->elipse.render(renderer, SDL2pp::Rect(x - 75 - camaraLimiteIzquierdo, y - 75 - camaraLimiteSuperior, 150, 150), flip);
    this->biff.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo, y - 30 - camaraLimiteSuperior, 60, 60), flip);
}

bool Explosion::animacion_completa() {
    return (this->circulo.completa() && this->elipse.completa() && this->biff.completa());
}
