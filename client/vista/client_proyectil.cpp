#include "client_proyectil.h"

AnimacionProyectil::AnimacionProyectil(SDL2pp::Renderer &renderer): texture(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0))), 
                                                                          size(this->texture->GetWidth()),
                                                                          x(0),
                                                                          y(0),
                                                                          angulo(0),
                                                                          direccion(1),
                                                                          currentFrame(12),
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
        renderizar_movimiento(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior);
    
    } else if (this->estado == EXPLOTAR) {
        renderizar_explosion(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior);
    }
}

void AnimacionProyectil::renderizar_movimiento(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    renderer.Copy(
        *this->texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x - (this->size/2) - camaraLimiteIzquierdo, this->y - (this->size/2) - camaraLimiteSuperior, this->size, this->size), this->angulo - 45,
        SDL2pp::NullOpt,
        this->direccion ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE
    );
}

void AnimacionProyectil::renderizar_explosion(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL2pp::Texture explosion(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0));
    int tamañoExplosion = explosion.GetWidth();;

    SDL2pp::Texture circulo(renderer, SDL2pp::Surface(DATA_PATH "/circle50.png").SetColorKey(true, 0));
    int tamañoCirculo = circulo.GetWidth();

    SDL2pp::Texture elipse(renderer, SDL2pp::Surface(DATA_PATH "/elipse50.png").SetColorKey(true, 0));
    int tamañoELipse = elipse.GetWidth();

    if (this->currentFrame < (explosion.GetHeight() / explosion.GetWidth())) {
        renderer.Copy(
            circulo,
            SDL2pp::Rect(0, (tamañoCirculo) * currentFrame, tamañoCirculo, tamañoCirculo),
            SDL2pp::Rect(this->x - 50 - camaraLimiteIzquierdo, this->y - 50 - camaraLimiteSuperior, tamañoCirculo, tamañoCirculo)
        );

        renderer.Copy(
            elipse,
            SDL2pp::Rect(0, (tamañoELipse) * currentFrame, tamañoELipse, tamañoELipse),
            SDL2pp::Rect(this->x - 75 - camaraLimiteIzquierdo, this->y - 75 - camaraLimiteSuperior, tamañoELipse, tamañoELipse)
        );

        renderer.Copy(
            explosion,
            SDL2pp::Rect(0, (tamañoExplosion) * currentFrame, tamañoExplosion, tamañoExplosion),
            SDL2pp::Rect(this->x - 30 - camaraLimiteIzquierdo, this->y - 30 - camaraLimiteSuperior, tamañoExplosion, tamañoExplosion)
        );
    }

    if (this->currentFrame > (explosion.GetHeight() / explosion.GetWidth())) {
        this->estado = EXPLOTO;
    } else {
        this->currentFrame++;
    }
}

/******************** ACTUALIZAR TEXTURA ********************/

void AnimacionProyectil::cambiar(std::shared_ptr<SDL2pp::Texture> texturaProyectil) {
    this->texture = texturaProyectil;
    this->size = this->texture->GetWidth();
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
