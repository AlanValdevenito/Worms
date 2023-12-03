#include "animacion_misil.h"

AnimacionMisil::AnimacionMisil(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos):   
    AnimacionArma(ARMA_MOVIENDOSE), 
    texturas(texturas), 
    movimiento(texturas[27]), 
    explosion(texturas, texturas[20]),
    sonido(sonidos[4]) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionMisil::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->humo.push_back(AnimacionHumo(this->texturas[40], this->x, this->y));
    
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
}

void AnimacionMisil::render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_MOVIENDOSE) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (30) - camaraLimiteSuperior, 60, 60), flip, 180);
    
    } else if (this->estado == ARMA_EXPLOTAR) {
        this->explosion.render(renderer, this->x, this->y, camaraLimiteIzquierdo, camaraLimiteSuperior);
        this->sonido.reproducir();
        
        if (this->explosion.animacion_completa()) {
            this->estado = ARMA_EXPLOTO;
        } else {
            this->explosion.update();
        }
    }

    renderizar_humo(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior);
}

void AnimacionMisil::renderizar_humo(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    for(int i = 0; i < (int) this->humo.size(); i++) {
        this->humo[i].render(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior);
    }
}
