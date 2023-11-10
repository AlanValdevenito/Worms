#include "client_granada.h"

Granada::Granada(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0))), 
                                                                          size(this->texture.GetWidth()),
                                                                          x(0),
                                                                          y(0),
                                                                          exploto(1),
                                                                          currentFrame(0) {}

// En Box2D la granada es una caja de 5m x 5m
 
void Granada::render(SDL2pp::Renderer &renderer) {
    this->texture.Update(SDL2pp::NullOpt, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0));
    this->size = this->texture.GetWidth();

    renderer.Copy(
        texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x - 8, this->y - 8, this->size, this->size)
    );
}

void Granada::update(float nuevoX, float nuevoY) {
    this->x = nuevoX;
    this->y = nuevoY;
}

void Granada::explotar(SDL2pp::Renderer &renderer) {
    SDL2pp::Texture explosion(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0));

    int tamaño = 60;

    if (this->currentFrame < 12) {
        renderer.Copy(
            explosion,
            SDL2pp::Rect(0, (tamaño) * currentFrame, tamaño, tamaño),
            SDL2pp::Rect(this->x - 16, this->y - 16, tamaño, tamaño)
        );
    }

    this->currentFrame++;
}

void Granada::set_flag(int flag) {
    this->exploto = flag;

    if (flag == 1) {
        this->currentFrame = 0;
    }
}

int Granada::get_flag() {
    return this->exploto;
}
