#include "vista_granada_verde.h"

AnimacionGranadaVerde::AnimacionGranadaVerde(SDL2pp::Renderer &renderer): Arma(ARMA_APUNTANDO), 
                                                                          movimiento(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/grenade.png").SetColorKey(true, 0))), 
                                                                          explosion(renderer), 
                                                                          apuntado(renderer, std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wthrgrn.png").SetColorKey(true, 0))), 
                                                                          tiempo(5) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionGranadaVerde::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
    this->angulo = nuevoAngulo;
    this->tiempo = nuevoTiempo;
}

void AnimacionGranadaVerde::render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_APUNTANDO) {
        this->apuntado.render(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior, direccion);
    }

    else if (this->estado == ARMA_MOVIENDOSE) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (30) - camaraLimiteSuperior, 60, 60), flip, this->angulo);
    
    } else if (this->estado == ARMA_EXPLOTAR) {
        this->explosion.render(renderer, this->x, this->y, camaraLimiteIzquierdo, camaraLimiteSuperior);
        
        if (this->explosion.animacion_completa()) {
            this->estado = ARMA_EXPLOTO;
        } else {
            this->explosion.update();
        }
    }

}

void AnimacionGranadaVerde::renderizar_tiempo(SDL2pp::Renderer &renderer) {

}

/******************** TIEMPO ********************/

void AnimacionGranadaVerde::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int AnimacionGranadaVerde::get_tiempo() {
    return this->tiempo;
}

/******************** ANGULO ********************/

void AnimacionGranadaVerde::aumentar_angulo() {
    this->apuntado.aumentar_angulo();
}

void AnimacionGranadaVerde::decrementar_angulo() {
    this->apuntado.decrementar_angulo();
}

int AnimacionGranadaVerde::get_angulo() {
    return this->apuntado.get_angulo();
}

/******************** POTENCIA ********************/

void AnimacionGranadaVerde::aumentar_potencia() {
    this->apuntado.aumentar_potencia();
}

int AnimacionGranadaVerde::get_potencia() {
    return this->apuntado.get_potencia();
}
