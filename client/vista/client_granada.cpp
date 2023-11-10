#include "client_granada.h"

Granada::Granada(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0))), 
                                                                          size(this->texture.GetWidth()),
                                                                          x(0),
                                                                          y(0),
                                                                          exploto(1) {}

void Granada::render(SDL2pp::Renderer &renderer) {
    this->texture.Update(SDL2pp::NullOpt, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0));
    this->size = this->texture.GetWidth();

    renderer.Copy(
        texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x, this->y , this->size, this->size)
    );
}

void Granada::update(float nuevoX, float nuevoY) {
    this->x = nuevoX;
    this->y = nuevoY;
}

void Granada::explotar(SDL2pp::Renderer &renderer) {
    /*this->texture.Update(SDL2pp::NullOpt, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0));
    this->size = this->texture.GetWidth();;

    int currentFrame = 12;
    for (int i = 0; i < 11; i++) {
        std::cout << currentFrame << std::endl;
        renderer.Copy(
            texture,
            SDL2pp::Rect(0, (this->size) * currentFrame, this->size, this->size),
            SDL2pp::Rect(this->x, this->y , this->size, this->size)
        );
    
        currentFrame--;
    }*/
}

void Granada::set_flag(int flag) {
    this->exploto = flag;
}

int Granada::get_flag() {
    return this->exploto;
}
