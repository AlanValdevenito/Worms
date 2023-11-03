#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

#define OFFSET_X -30
#define OFFSET_Y -55

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
    this->animacion.render(renderer, SDL2pp::Rect(x + OFFSET_X, y + OFFSET_Y, ANCHO_SPRITE, ALTO_SPRITE), flip);

    this->render_vida(renderer);
 
    if (this->miraActivada) {
        this->mira.render(renderer, x + OFFSET_X, y + OFFSET_Y, this->mirandoIzquierda);
    } 

    if (this->miraActivada) {
        this->potencia.render(renderer, x + OFFSET_X, y + OFFSET_Y, this->mirandoIzquierda);
    } 

}

void Worm::render_vida(SDL2pp::Renderer &renderer) {
	// SDL2pp::Texture etiqueta(renderer, Surface(DATA_PATH "/boton.png").SetColorKey(true, 0));
	// etiqueta.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la fuente de la letra
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 12);

    int altura = renderer.GetOutputHeight();

    SDL2pp::Rect borde(this->x + 13, altura - 330, 29, 21);
    SDL2pp::Color blanco(255, 255, 255, 255);
    renderer.SetDrawColor(blanco);
    renderer.FillRect(borde);

    SDL2pp::Rect contenedor(this->x + 15, altura - 329, 25, 17);
    SDL2pp::Color negro(0,0,0,255);
    renderer.SetDrawColor(negro);
    renderer.FillRect(contenedor);

    SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->vida), blanco);
    SDL2pp::Texture texture(renderer, surface);

    SDL2pp::Rect vida(this->x + 15, altura - 329, surface.GetWidth(), surface.GetHeight());
    renderer.Copy(texture, SDL2pp::NullOpt, vida);
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
