#include "animacion_mortero.h"

AnimacionMortero::AnimacionMortero(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos): 
    AnimacionArma(ARMA_APUNTANDO), 
    texturas(texturas), 
    movimiento(texturas[29]), 
    explosion(texturas, texturas[20]), 
    apuntado(renderer, texturas[33]),
    sonido(sonidos[4]) 
{
    for (int i = 1; i <= 6; i++){
        this->fragmentos[i] = std::make_unique<AnimacionFragmento>(renderer, texturas, sonidos);
    }
}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionMortero::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {

    if ((this->estado == ARMA_EXPLOTO) || (this->estado == ARMA_EXPLOTAR)) {
        this->fragmentos[id]->update(nuevoX, nuevoY, nuevoEstado, nuevoAngulo);
    } else {
        this->humo.push_back(AnimacionHumo(this->texturas[40], this->x, this->y));

        this->x = nuevoX;
        this->y = nuevoY;
        this->estado = nuevoEstado;
        this->angulo = nuevoAngulo;
        this->direccion = nuevaDireccion;
    }

}

void AnimacionMortero::render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_APUNTANDO) {
        this->apuntado.render(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior, direccion);
    }

    else if (this->estado == ARMA_MOVIENDOSE) {
        SDL_RendererFlip flip = this->direccion ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
        int offset = this->direccion ? 180 : (-90);
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (30) - camaraLimiteSuperior, 60, 60), flip, this->angulo - offset);
    
    } else if (this->estado == ARMA_EXPLOTAR) {
        this->explosion.render(renderer, this->x, this->y, camaraLimiteIzquierdo, camaraLimiteSuperior);
        this->sonido.reproducir();
        
        if (this->explosion.animacion_completa()) {
            this->estado = ARMA_EXPLOTO;
        } else {
            this->explosion.update();
        }
    }
 
    if ((this->estado == ARMA_EXPLOTO) || (this->estado == ARMA_EXPLOTAR)) {

        for (auto &elemento : this->fragmentos)
        {
            (elemento.second)->render(renderer, color, camaraLimiteIzquierdo, camaraLimiteSuperior, direccion);
        }

    }

    renderizar_humo(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior);
}

void AnimacionMortero::renderizar_humo(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    for(int i = 0; i < (int) this->humo.size(); i++) {
        this->humo[i].render(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior);
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
