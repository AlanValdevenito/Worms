#include "client_granada.h"

Granada::Granada(SDL2pp::Renderer &renderer, float x, float y): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0))), 
                                                                          size(this->texture.GetWidth()),
                                                                          x(x),
                                                                          y(y) {}

void Granada::render(SDL2pp::Renderer &renderer) {
    renderer.Copy(
        texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x, this->y , this->size, this->size)
    );
}
