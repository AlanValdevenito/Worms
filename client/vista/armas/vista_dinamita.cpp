#include "vista_dinamita.h"

AnimacionDinamita::AnimacionDinamita(SDL2pp::Renderer &renderer): Arma(ARMA_MOVIENDOSE), 
                                                                  movimiento(std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/dynamite.png").SetColorKey(true, 0)), false), 
                                                                  explosion(renderer, std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0))),
                                                                  sonido("/sonidos/armas/EXPLOSION1.WAV"), 
                                                                  tiempo(5) {}

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void AnimacionDinamita::update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo, int nuevaDireccion, int nuevoTiempo, int id) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->estado = nuevoEstado;
    this->tiempo = nuevoTiempo;
}

void AnimacionDinamita::render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) {

    if (this->estado == ARMA_MOVIENDOSE) {
        this->movimiento.update();

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        this->movimiento.render(renderer, SDL2pp::Rect(this->x - (30) - camaraLimiteIzquierdo, this->y - (38) - camaraLimiteSuperior, 60, 60), flip, 0);
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

void AnimacionDinamita::renderizar_tiempo(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 18);
    SDL2pp::Color blanco(255, 255, 255, 255); 
    SDL2pp::Color negro(0, 0, 0, 0);

    SDL2pp::Texture borde(renderer, SDL2pp::Surface(DATA_PATH "/borde.png").SetColorKey(true, 0));

    renderer.Copy(
        borde,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x - 19 - camaraLimiteIzquierdo, this->y - 48 - camaraLimiteSuperior, 35, 25)
    );

    SDL2pp::Rect contenedor(this->x - 16 - camaraLimiteIzquierdo, this->y - 45 - camaraLimiteSuperior, 28, 18);

	renderer.SetDrawColor(negro); 
	renderer.FillRect(contenedor);

	SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->tiempo), color);
	SDL2pp::Texture texture(renderer, surface);

    SDL2pp::Rect mensaje(this->x - 8 - camaraLimiteIzquierdo, this->y - 47 - camaraLimiteSuperior, surface.GetWidth(), surface.GetHeight());

	renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
}

/******************** TIEMPO ********************/

void AnimacionDinamita::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int AnimacionDinamita::get_tiempo() {
    return this->tiempo;
}
