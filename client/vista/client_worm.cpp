#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

#define OFFSET 8 // Definimos un offset ya que debemos hacer un corrimiento en 'x' e 'y' ya que las fisicas modeladas con Box2D
                 // tienen el (0,0) de los cuerpos en el centro

Worm::Worm(SDL2pp::Texture &texture, SDL2pp::Texture &potencia, float x, float y, int vida) : animacion(texture), mira(Mira()), potencia(potencia), miraActivada(false), mirandoIzquierda(true), x(x), y(y), vida(vida) {
    
}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos. Esto les va a resultar muy util.

void Worm::update(int it, float nuevoX, float nuevoY, int nuevaVida)
{

    if ((nuevoX != this->x) || (nuevoY != this->y)) {
    
        this->animacion.update(it);

        if (nuevoX < this->x)
        {
            this->mirandoIzquierda = true;
        
        } else if (nuevoX > this->x)
        {
            this->mirandoIzquierda = false;
        }

        this->x = nuevoX;
        this->y = nuevoY;
        this->vida = nuevaVida;
    }
}

void Worm::activar_mira() {
    this->miraActivada = true;
}

void Worm::desactivar_mira() {
    this->miraActivada = false;
}

bool Worm::get_mira() {
    return this->miraActivada;
}

void Worm::render(SDL2pp::Renderer &renderer)
{
    SDL_RendererFlip flip = this->mirandoIzquierda ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    this->animacion.render(renderer, SDL2pp::Rect(x - OFFSET, y - OFFSET, ANCHO_SPRITE, ALTO_SPRITE), flip);

    this->render_vida(renderer);
 
    if (this->miraActivada) {
        this->mira.render(renderer, x - OFFSET, y - OFFSET, this->mirandoIzquierda);
    } 

    if (this->miraActivada) {
        this->potencia.render(renderer, x - OFFSET, y - OFFSET, this->mirandoIzquierda);
    } 

}

void Worm::render_vida(SDL2pp::Renderer &renderer) {
	SDL2pp::Texture etiqueta(renderer, SDL2pp::Surface(DATA_PATH "/boton.png").SetColorKey(true, 0));
	etiqueta.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la fuente de la letra
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 15);

    // int altura = renderer.GetOutputHeight();

    SDL2pp::Rect posicionEtiqueta(this->x + 5, this->y - 15, 28, 18);
	renderer.Copy(etiqueta, SDL2pp::NullOpt, posicionEtiqueta);

	SDL2pp::Color negro(0,0,0,255);
	SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->vida), negro);
	SDL2pp::Texture texture(renderer, surface);

	SDL2pp::Rect mensaje(this->x + 4, this->y - 15, surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
}

void Worm::aumentar_potencia() {
    if (this->miraActivada) {
        this->potencia.update();
    }
}

void Worm::reiniciar_potencia() {
    if (this->miraActivada) {
        this->potencia.reiniciar();
    }
}

int Worm::get_potencia() {
    if (this->miraActivada) {
        return this->potencia.get_current_frame();
    } 

    return 0;
}

int Worm::get_vida() {
    return this->vida;
}
