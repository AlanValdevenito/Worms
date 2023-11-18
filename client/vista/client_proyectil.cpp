#include "client_proyectil.h"

AnimacionProyectil::AnimacionProyectil(SDL2pp::Renderer &renderer): movimiento(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0))),
                                                                    explosion(renderer),
                                                                    x(0),
                                                                    y(0),
                                                                    angulo(0),
                                                                    direccion(1),
                                                                    tiempo(5),
                                                                    estado(APUNTANDO_PROYECTIL) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionProyectil::update(float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion, int nuevoEstado) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->angulo = nuevoAngulo;
    this->direccion = nuevaDireccion;
    this->estado = nuevoEstado;
}

void AnimacionProyectil::render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {

    if (this->estado == MOVIENDOSE_PROYECTIL) {
        SDL_RendererFlip flip = this->direccion ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (32/2) - camaraLimiteIzquierdo, this->y - (32/2) - camaraLimiteSuperior, 32, 32), flip, this->angulo - 45);
    
    } else if (this->estado == EXPLOTAR) {
        this->explosion.render(renderer, this->x, this->y, camaraLimiteIzquierdo, camaraLimiteSuperior);
        
        if (this->explosion.animacion_completa()) {
            this->estado = EXPLOTO;
        } else {
            this->explosion.update();
        }
    }
}

/******************** ACTUALIZAR TEXTURA ********************/

void AnimacionProyectil::cambiar(std::shared_ptr<SDL2pp::Texture> texturaProyectil) {
    this->movimiento.cambiar(texturaProyectil);
}

/******************** TIEMPO DE EXPLOSION ********************/

void AnimacionProyectil::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int AnimacionProyectil::get_tiempo() {
    return this->tiempo;
}

/******************** GETTERS ********************/

int AnimacionProyectil::get_estado() {
    return this->estado;
}
