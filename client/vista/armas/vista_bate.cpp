#include "vista_bate.h"

AnimacionBateDeBaseball::AnimacionBateDeBaseball(SDL2pp::Renderer &renderer): Arma(ARMA_APUNTANDO), 
                                                                              apuntado(renderer, std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbsbaim.png").SetColorKey(true, 0))) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionBateDeBaseball::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
    this->angulo = nuevoAngulo;
}

void AnimacionBateDeBaseball::render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_APUNTANDO) {
        // std::cout << "Renderizando Bate" << std::endl;
        this->apuntado.render(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior, direccion);
    }

}

/******************** ANGULO ********************/

void AnimacionBateDeBaseball::aumentar_angulo() {
    this->apuntado.aumentar_angulo();
}

void AnimacionBateDeBaseball::decrementar_angulo() {
    this->apuntado.decrementar_angulo();
}

int AnimacionBateDeBaseball::get_angulo() {
    return this->apuntado.get_angulo();
}
