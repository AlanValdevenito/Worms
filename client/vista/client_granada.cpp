#include "client_granada.h"

Granada::Granada(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0))), 
                                                                          size(this->texture.GetWidth()),
                                                                          x(0),
                                                                          y(0),
                                                                          seLanzo(false),
                                                                          exploto(1),
                                                                          currentFrame(12),
                                                                          tiempo(5) {}

// En Box2D la granada es una caja de 5m x 5m
 
void Granada::render(SDL2pp::Renderer &renderer, float camara) {
    this->texture.Update(SDL2pp::NullOpt, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0));
    this->size = this->texture.GetWidth();

    renderer.Copy(
        texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x - 8 - camara, this->y - 8, this->size, this->size)
    );
}

void Granada::update(float nuevoX, float nuevoY) {
    this->x = nuevoX;
    this->y = nuevoY;
}

void Granada::explotar(SDL2pp::Renderer &renderer, float camara) {
    SDL2pp::Texture explosion(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0));

    int tamaño = 60;

    if (this->currentFrame < 12) {
        renderer.Copy(
            explosion,
            SDL2pp::Rect(0, (tamaño) * currentFrame, tamaño, tamaño),
            SDL2pp::Rect(this->x - 16 - camara, this->y - 16, tamaño, tamaño)
        );
    }

    this->currentFrame++;
}

void Granada::lanzarGranada() {
    this->seLanzo = true;
}

bool Granada::seLanzoGranada() {
    return this->seLanzo;
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

float Granada::get_x() {
    return this->x;
}

float Granada::get_y() {
    return this->y;
}

void Granada::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int Granada::get_tiempo() {
    return this->tiempo;
}
