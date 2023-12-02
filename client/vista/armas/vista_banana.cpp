#include "vista_banana.h"

AnimacionBanana::AnimacionBanana(SDL2pp::Renderer &renderer, std::shared_ptr<SDL2pp::Chunk> sonido): Arma(ARMA_APUNTANDO), 
                                                              movimiento(std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/banana.png").SetColorKey(true, 0))), 
                                                              explosion(renderer, std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/expow.png").SetColorKey(true, 0))), 
                                                              apuntado(renderer, std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wthrban.png").SetColorKey(true, 0))), 
                                                              sonido(sonido),
                                                              tiempo(5) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionBanana::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
    this->angulo = nuevoAngulo;
    this->tiempo = nuevoTiempo;
}

void AnimacionBanana::render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_APUNTANDO) {
        this->apuntado.render(renderer, camaraLimiteIzquierdo, camaraLimiteSuperior, direccion);
    }

    else if (this->estado == ARMA_MOVIENDOSE) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (30) - camaraLimiteSuperior, 60, 60), flip, this->angulo);
        renderizar_tiempo(renderer, color, camaraLimiteIzquierdo, camaraLimiteSuperior);

    } else if (this->estado == ARMA_EXPLOTAR) {
        this->explosion.render(renderer, this->x, this->y, camaraLimiteIzquierdo, camaraLimiteSuperior);
        this->sonido.reproducir();
        
        if (this->explosion.animacion_completa()) {
            this->estado = ARMA_EXPLOTO;
        } else {
            this->explosion.update();
        }
    }

}

void AnimacionBanana::renderizar_tiempo(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 18);
    SDL2pp::Color blanco(255, 255, 255, 255); 
    SDL2pp::Color negro(0, 0, 0, 0);

    SDL2pp::Texture borde(renderer, SDL2pp::Surface(DATA_PATH "/borde.png").SetColorKey(true, 0));

    renderer.Copy(
        borde,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x - 19 - camaraLimiteIzquierdo, this->y - 40 - camaraLimiteSuperior, 35, 25)
    );

    SDL2pp::Rect contenedor(this->x - 16 - camaraLimiteIzquierdo, this->y - 37 - camaraLimiteSuperior, 28, 18);

	renderer.SetDrawColor(negro); 
	renderer.FillRect(contenedor);

	SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->tiempo), color);
	SDL2pp::Texture texture(renderer, surface);

    SDL2pp::Rect mensaje(this->x - 8 - camaraLimiteIzquierdo, this->y - 39 - camaraLimiteSuperior, surface.GetWidth(), surface.GetHeight());

	renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
}

/******************** TIEMPO ********************/

void AnimacionBanana::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int AnimacionBanana::get_tiempo() {
    return this->tiempo;
}

/******************** ANGULO ********************/

void AnimacionBanana::aumentar_angulo() {
    this->apuntado.aumentar_angulo();
}

void AnimacionBanana::decrementar_angulo() {
    this->apuntado.decrementar_angulo();
}

int AnimacionBanana::get_angulo() {
    return this->apuntado.get_angulo();
}

/******************** POTENCIA ********************/

void AnimacionBanana::aumentar_potencia() {
    this->apuntado.aumentar_potencia();
}

int AnimacionBanana::get_potencia() {
    return this->apuntado.get_potencia();
}