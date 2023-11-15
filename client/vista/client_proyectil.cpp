#include "client_proyectil.h"

AnimacionProyectil::AnimacionProyectil(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0))), 
                                                                          size(this->texture.GetWidth()),
                                                                          x(0),
                                                                          y(0),
                                                                          angulo(0),
                                                                          direccion(1),
                                                                          seLanzo(false),
                                                                          exploto(0),
                                                                          currentFrame(12),
                                                                          tiempo(5) {}

void AnimacionProyectil::render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    renderer.Copy(
        this->texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x - 8 - camaraLimiteIzquierdo, this->y - 8 - camaraLimiteSuperior, this->size, this->size), this->angulo - 45,
        SDL2pp::NullOpt,    // rotation center - not needed
        this->direccion ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE
    );
}

void AnimacionProyectil::update(float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->angulo = nuevoAngulo;
    this->direccion = nuevaDireccion;
}

void AnimacionProyectil::cambiar(std::string &ruta) {
    SDL2pp::Surface surface(DATA_PATH + ruta);

    this->size = surface.GetWidth();
    this->texture.Update(SDL2pp::NullOpt, surface.SetColorKey(true, 0));
}

void AnimacionProyectil::explotar(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL2pp::Texture explosion(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0));

    SDL2pp::Texture circulo(renderer, SDL2pp::Surface(DATA_PATH "/circle50.png").SetColorKey(true, 0));
    int tamañoCirculo = circulo.GetWidth();

    int tamaño = 60;

    if (this->currentFrame < 12) {

        renderer.Copy(
            circulo,
            SDL2pp::Rect(0, (tamañoCirculo) * currentFrame, tamañoCirculo, tamañoCirculo),
            SDL2pp::Rect(this->x - 50 - camaraLimiteIzquierdo, this->y - 50 - camaraLimiteSuperior, tamañoCirculo, tamañoCirculo)
        );

        renderer.Copy(
            explosion,
            SDL2pp::Rect(0, (tamaño) * currentFrame, tamaño, tamaño),
            SDL2pp::Rect(this->x - 30 - camaraLimiteIzquierdo, this->y - 30 - camaraLimiteSuperior, tamaño, tamaño)
        );

    }

    this->currentFrame++;
}

void AnimacionProyectil::lanzarProyectil() {
    this->seLanzo = true;
}

bool AnimacionProyectil::seLanzoProyectil() {
    return this->seLanzo;
}

void AnimacionProyectil::set_flag(int flag) {
    this->exploto = flag;

    // Si el flag es igual a 1 quiere decir que tiramos la bomba y debemos reiniciar el frame actual de la explosion
    if (flag == 1) {
        this->currentFrame = 0;
    }
}

int AnimacionProyectil::get_flag() {
    return this->exploto;
}

float AnimacionProyectil::get_x() {
    return this->x;
}

float AnimacionProyectil::get_y() {
    return this->y;
}

void AnimacionProyectil::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int AnimacionProyectil::get_tiempo() {
    return this->tiempo;
}
