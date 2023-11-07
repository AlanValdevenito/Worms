#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

#define OFFSET 16 // Definimos un offset ya que debemos hacer un corrimiento en 'x' e 'y' ya que las fisicas modeladas con Box2D
                 // tienen el (0,0) de los cuerpos en el centro

Worm::Worm(SDL2pp::Texture &texture, SDL2pp::Texture &arma, SDL2pp::Texture &potencia, float x, float y, int vida) : animacion(texture), arma(arma), mira(Mira()), potencia(potencia), armaEquipada(false), miraActivada(false), mirandoIzquierda(true), x(x), y(y), vida(vida) {
    
}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos. Esto les va a resultar muy util.

void Worm::update(int it, float nuevoX, float nuevoY, int nuevaVida)
{

    if (this->armaEquipada) {
        this->arma.update();
    }

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

void Worm::mirar_derecha() {
    this->mirandoIzquierda = false;
}

void Worm::mirar_izquierda() {
    this->mirandoIzquierda = true;
}


void Worm::equipar_arma() {
    this->armaEquipada = true;
    this->miraActivada = true;
}
void Worm::desequipar_arma() {
    this->armaEquipada = false;
    this->miraActivada = false;
    this->arma.reiniciar();
    this->mira.reiniciar();
    this->potencia.reiniciar();
}

bool Worm::arma_equipada() {
    return this->armaEquipada;
}

void Worm::aumentar_angulo() {
    this->mira.aumentar_angulo();
}

void Worm::decrementar_angulo() {
    this->mira.decrementar_angulo();
}

void Worm::render(SDL2pp::Renderer &renderer)
{
    SDL_RendererFlip flip = this->mirandoIzquierda ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    if (armaEquipada) {
        this->arma.render(renderer, SDL2pp::Rect(x - OFFSET, y - OFFSET, ANCHO_SPRITE, ALTO_SPRITE), flip);
    
    } else {
        this->animacion.render(renderer, SDL2pp::Rect(x - OFFSET, y - OFFSET, ANCHO_SPRITE, ALTO_SPRITE), flip);
    }
    
    this->render_vida(renderer);
 
    if (this->miraActivada) {
        this->mira.render(renderer, x - OFFSET, y - OFFSET, this->mirandoIzquierda);
        this->potencia.render(renderer, x - OFFSET, y - OFFSET, this->mirandoIzquierda, this->mira.get_angulo());
    } 

}

void Worm::render_vida(SDL2pp::Renderer &renderer) {
    // Cargamos la fuente de la letra
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 14);

	SDL2pp::Rect borde(this->x - 5, this->y - 30, 32, 22);
	SDL2pp::Color blanco(255, 255, 255, 255); 
	renderer.SetDrawColor(blanco);
	renderer.FillRect(borde);

	SDL2pp::Rect contenedor(this->x - 3, this->y - 28, 28, 18);
	//SDL2pp::Color negro(0,0,0,255);
    SDL2pp::Color verde(20,100,75,100);
	renderer.SetDrawColor(verde); 
	renderer.FillRect(contenedor);

	SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->vida), blanco);
	SDL2pp::Texture texture(renderer, surface);

	SDL2pp::Rect mensaje(this->x - 2, this->y - 28, surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
}

void Worm::aumentar_potencia() {
    if (this->miraActivada) {
        this->potencia.update();
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

int Worm::get_angulo() {
    return this->mira.get_angulo();
}
