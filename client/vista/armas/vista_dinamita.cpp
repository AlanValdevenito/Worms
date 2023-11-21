#include "vista_dinamita.h"

AnimacionDinamita::AnimacionDinamita(SDL2pp::Renderer &renderer): Arma(ARMA_MOVIENDOSE), 
                                                                  movimiento(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/dynamite.png").SetColorKey(true, 0))), 
                                                                  explosion(renderer), 
                                                                  tiempo(5) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionDinamita::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
    this->tiempo = nuevoTiempo;
}

void AnimacionDinamita::render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_MOVIENDOSE) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (30) - camaraLimiteSuperior, 60, 60), flip, 0);
    
    } else if (this->estado == ARMA_EXPLOTAR) {
        this->explosion.render(renderer, this->x, this->y, camaraLimiteIzquierdo, camaraLimiteSuperior);
        
        if (this->explosion.animacion_completa()) {
            this->estado = ARMA_EXPLOTO;
        } else {
            this->explosion.update();
        }
    }

}

void AnimacionDinamita::renderizar_tiempo(SDL2pp::Renderer &renderer) {

}

/******************** TIEMPO ********************/

void AnimacionDinamita::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int AnimacionDinamita::get_tiempo() {
    return this->tiempo;
}
