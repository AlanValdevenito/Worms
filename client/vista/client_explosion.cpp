#include "client_explosion.h"

AnimacionExplosion::AnimacionExplosion(std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::shared_ptr<SDL2pp::Texture> ex):  
    ex(ex, false),
    circulo(texturas[37], false),
    elipse(texturas[38], false),
    fuego(texturas[39], false),
    movimientoFuego(0) {}

void AnimacionExplosion::update() {
    this->fuego.update();
    this->circulo.update();
    this->elipse.update();
    this->ex.update();
}

void AnimacionExplosion::render(SDL2pp::Renderer &renderer, float x, float y, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
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

    if (not this->ex.completa()) {
        this->ex.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo, y - 30 - camaraLimiteSuperior, 60, 60), flip);
    }
    
    movimientoFuego += 1;
}

bool AnimacionExplosion::animacion_completa() {
    return (this->fuego.completa() && this->circulo.completa() && this->elipse.completa() && this->ex.completa());
}
