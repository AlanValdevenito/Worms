#include "vista_granada_roja.h"

AnimacionGranadaRoja::AnimacionGranadaRoja(SDL2pp::Renderer &renderer): Arma(ARMA_APUNTANDO), 
                                                                          movimiento(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/cluster.png").SetColorKey(true, 0))), 
                                                                          explosion(renderer), 
                                                                          apuntado(renderer, std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wthrcls.png").SetColorKey(true, 0))), 
                                                                          tiempo(5) 
{

    for (int i = 1; i <= 6; i++){
        this->fragmentos[i] = std::make_shared<AnimacionFragmento>(renderer);
    }

}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionGranadaRoja::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {

    if ((this->estado == ARMA_EXPLOTO) || (this->estado == ARMA_EXPLOTAR)) {
        this->fragmentos[id]->update(nuevoX, nuevoY, nuevoEstado, nuevoAngulo);
    } else {
        this->x = nuevoX;
        this->y = nuevoY;
        this->estado = nuevoEstado;
        this->angulo = nuevoAngulo;
        this->tiempo = nuevoTiempo;
    }

}

void AnimacionGranadaRoja::render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

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
    
    if ((this->estado == ARMA_EXPLOTO) || (this->estado == ARMA_EXPLOTAR)) {

        for (auto &elemento : this->fragmentos)
        {
            (elemento.second)->render(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior, direccion);
        }

    }

}

void AnimacionGranadaRoja::renderizar_tiempo(SDL2pp::Renderer &renderer) {

}

/******************** TIEMPO ********************/

void AnimacionGranadaRoja::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int AnimacionGranadaRoja::get_tiempo() {
    return this->tiempo;
}

/******************** ANGULO ********************/

void AnimacionGranadaRoja::aumentar_angulo() {
    this->apuntado.aumentar_angulo();
}

void AnimacionGranadaRoja::decrementar_angulo() {
    this->apuntado.decrementar_angulo();
}

int AnimacionGranadaRoja::get_angulo() {
    return this->apuntado.get_angulo();
}

/******************** POTENCIA ********************/

void AnimacionGranadaRoja::aumentar_potencia() {
    this->apuntado.aumentar_potencia();
}

int AnimacionGranadaRoja::get_potencia() {
    return this->apuntado.get_potencia();
}
