#include "animacion_humo.h"

AnimacionHumo::AnimacionHumo(std::shared_ptr<SDL2pp::Texture> textura, int x, int y): animacion(textura, false), x(x), y(y) {}

void AnimacionHumo::render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {

    if (this->animacion.completa()) {
        return;
    }

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    this->animacion.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (30) - camaraLimiteSuperior, 60, 60), flip);
    this->animacion.update();
}
