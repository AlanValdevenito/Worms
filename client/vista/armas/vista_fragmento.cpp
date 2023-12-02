#include "vista_fragmento.h"

AnimacionFragmento::AnimacionFragmento(SDL2pp::Renderer &renderer): Arma(ARMA_MOVIENDOSE), 
                                                                    movimiento(std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/clustlet.png").SetColorKey(true, 0))), 
                                                                    explosion(renderer, std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exfoom.png").SetColorKey(true, 0))),
                                                                    sonido("/sonidos/armas/EXPLOSION1.WAV") {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionFragmento::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
    this->angulo = nuevoAngulo;
}

void AnimacionFragmento::render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_MOVIENDOSE) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (30) - camaraLimiteSuperior, 60, 60), flip, this->angulo);

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
