#include "vista_ataque_aereo.h"

AnimacionAtaqueAereo::AnimacionAtaqueAereo(SDL2pp::Renderer &renderer): Arma(ARMA_MOVIENDOSE) {

    for (int i = 1; i <= 6; i++){
        this->misiles[i] = std::make_unique<AnimacionMisil>(renderer, std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0)));
    }
    
}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionAtaqueAereo::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->misiles[id]->update(nuevoX, nuevoY, nuevoEstado, nuevoAngulo, nuevaDireccion, nuevoTiempo);
}

void AnimacionAtaqueAereo::render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    for (auto &elemento : this->misiles)
    {
        (elemento.second)->render(renderer, color, camaraLimiteIzquierdo, camaraLimiteSuperior, direccion);
    }

}
