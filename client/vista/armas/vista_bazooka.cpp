#include "vista_bazooka.h"

AnimacionBazooka::AnimacionBazooka(SDL2pp::Renderer &renderer): Arma(ARMA_APUNTANDO), 
                                                                movimiento(std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/missile.png").SetColorKey(true, 0))), 
                                                                explosion(renderer, std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0))), 
                                                                apuntado(renderer, std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbaz.png").SetColorKey(true, 0))) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionBazooka::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
    this->angulo = nuevoAngulo;
    this->direccion = nuevaDireccion;
}

void AnimacionBazooka::render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

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

void AnimacionBazooka::aumentar_angulo() {
    this->apuntado.aumentar_angulo();
}

void AnimacionBazooka::decrementar_angulo() {
    this->apuntado.decrementar_angulo();
}

int AnimacionBazooka::get_angulo() {
    return this->apuntado.get_angulo();
}

/******************** POTENCIA ********************/

void AnimacionBazooka::aumentar_potencia() {
    this->apuntado.aumentar_potencia();
}

int AnimacionBazooka::get_potencia() {
    return this->apuntado.get_potencia();
}
