#include "vista_misil.h"

AnimacionMisil::AnimacionMisil(SDL2pp::Renderer &renderer, std::unique_ptr<SDL2pp::Texture> ex, std::shared_ptr<SDL2pp::Chunk> sonido):   Arma(ARMA_MOVIENDOSE), 
                                                                                                    movimiento(std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/airmisl.png").SetColorKey(true, 0))), 
                                                                                                    explosion(renderer, std::move(ex)),
                                                                                                    sonido(sonido) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionMisil::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
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

}
