#include "vista_mortero.h"

AnimacionMortero::AnimacionMortero(SDL2pp::Renderer &renderer): Arma(ARMA_APUNTANDO), 
                                                                movimiento(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/mortar.png").SetColorKey(true, 0))), 
                                                                explosion(renderer), 
                                                                apuntado(renderer, std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbaz.png").SetColorKey(true, 0))) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionMortero::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
    this->angulo = nuevoAngulo;
    this->direccion = nuevaDireccion;
}

void AnimacionMortero::render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_APUNTANDO) {
        this->apuntado.render(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior, direccion);
    }

    else if (this->estado == ARMA_MOVIENDOSE) {
        SDL_RendererFlip flip = this->direccion ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
        int offset = this->direccion ? 180 : (-90);
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (30) - camaraLimiteSuperior, 60, 60), flip, this->angulo - offset);
    
    } else if (this->estado == ARMA_EXPLOTAR) {
        this->explosion.render(renderer, this->x, this->y, camaraLimiteIzquierdo, camaraLimiteSuperior);
        
        if (this->explosion.animacion_completa()) {
            this->estado = ARMA_EXPLOTO;
        } else {
            this->explosion.update();
        }
    }

}

/******************** ANGULO ********************/

void AnimacionMortero::aumentar_angulo() {
    this->apuntado.aumentar_angulo();
}

void AnimacionMortero::decrementar_angulo() {
    this->apuntado.decrementar_angulo();
}

int AnimacionMortero::get_angulo() {
    return this->apuntado.get_angulo();
}

/******************** POTENCIA ********************/

void AnimacionMortero::aumentar_potencia() {
    this->apuntado.aumentar_potencia();
}

int AnimacionMortero::get_potencia() {
    return this->apuntado.get_potencia();
}
