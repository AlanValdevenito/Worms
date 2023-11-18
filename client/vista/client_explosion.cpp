#include "client_explosion.h"

Explosion::Explosion(SDL2pp::Renderer &renderer): biff(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0)), false),
                                                  circulo(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/circle50.png").SetColorKey(true, 0)), false),
                                                  elipse(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/elipse50.png").SetColorKey(true, 0)), false) {}

void Explosion::update() {
    this->circulo.update(1);
    this->elipse.update(1);
    this->biff.update(1);
}

void Explosion::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    this->circulo.render(renderer, dest, flip);
    this->elipse.render(renderer, dest, flip);
    this->biff.render(renderer, dest, flip);
}
