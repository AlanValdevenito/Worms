#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

#define OFFSET_Y 8 // Definimos un offset ya que debemos hacer un corrimiento en 'x' e 'y' ya que las fisicas modeladas con Box2D
                 // tienen el (0,0) de los cuerpos en el centro

#define OFFSET_X 30

Worm::Worm(SDL2pp::Renderer &renderer, SDL2pp::Color &color, float x, float y, int vida): animacion(renderer), 
                                                                                          arma(renderer), 
                                                                                          armaEquipada(false), 
                                                                                          mirandoIzquierda(true), 
                                                                                          x(x), 
                                                                                          y(y), 
                                                                                          vida(vida),
                                                                                          color(color) {}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos. Esto les va a resultar muy util.

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void Worm::update(int it, float nuevoX, float nuevoY, int nuevaVida)
{

    if (this->armaEquipada) {
        this->arma.update();
    }

    if ((nuevoX != this->x) || (nuevoY != this->y)) {

        this->animacion.update(it);

        this->x = nuevoX;
        this->y = nuevoY;
        this->vida = nuevaVida;
    }
}

void Worm::render(SDL2pp::Renderer &renderer)
{
    SDL_RendererFlip flip = this->mirandoIzquierda ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    if (this->armaEquipada) {
        this->arma.render(renderer, x - OFFSET_X, y - OFFSET_Y, this->mirandoIzquierda);
    
    } else {
        this->animacion.render(renderer, SDL2pp::Rect(x - OFFSET_X, y - OFFSET_Y, ANCHO_SPRITE, ALTO_SPRITE), flip);
    }
    
    this->render_vida(renderer);
}

void Worm::render_vida(SDL2pp::Renderer &renderer) {
    // Cargamos la fuente de la letra
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 14);
    SDL2pp::Color blanco(255, 255, 255, 255); 

	SDL2pp::Rect borde(this->x - 18, this->y - 30, 32, 22);
    // SDL2pp::Rect borde(320 - 5, this->y - 30, 32, 22);
	renderer.SetDrawColor(blanco);
	renderer.FillRect(borde);

	SDL2pp::Rect contenedor(this->x - 16, this->y - 28, 28, 18);
    // SDL2pp::Rect contenedor(320 - 3, this->y - 28, 28, 18);
	//SDL2pp::Color negro(0,0,0,255);
	renderer.SetDrawColor(this->color); 
	renderer.FillRect(contenedor);

	SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->vida), blanco);
	SDL2pp::Texture texture(renderer, surface);

	SDL2pp::Rect mensaje(this->x - 15, this->y - 28, surface.GetWidth(), surface.GetHeight());
    // SDL2pp::Rect mensaje(320 - 2, this->y - 28, surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
}

/******************** DIRECCION ********************/

void Worm::mirar_derecha() {
    this->mirandoIzquierda = false;
}

void Worm::mirar_izquierda() {
    this->mirandoIzquierda = true;
}

/******************** ARMA ********************/

void Worm::equipar_arma(int tipo, std::string &ruta) {
    this->arma.equipar_arma(tipo, ruta);
    this->armaEquipada = true;
}

void Worm::desequipar_arma() {
    this->armaEquipada = false;
    this->arma.reiniciar();
}

int Worm::get_tipo_de_arma() {
    return this->arma.get_tipo();
}

bool Worm::arma_equipada() {
    return this->armaEquipada;
}

/******************** ANGULO ********************/

void Worm::aumentar_angulo() {
    this->arma.aumentar_angulo();
}

void Worm::decrementar_angulo() {
    this->arma.decrementar_angulo();
}

int Worm::get_angulo() {
    return this->arma.get_angulo();
}

/******************** POTENCIA ********************/

void Worm::aumentar_potencia() {
    if (this->armaEquipada) {
        this->arma.aumentar_potencia();
    }
}

int Worm::get_potencia() {
    if (this->armaEquipada) {
        return this->arma.get_potencia();
    } 

    return 0;
}

/******************** GETTERS GENERALES ********************/

int Worm::get_vida() {
    return this->vida;
}

float Worm::get_x() {
    return this->x;
}

float Worm::get_y() {
    return this->y;
}

/******************** SETTERS GENERALES ********************/

void Worm::set_x(float nuevoX) {
    this->x = nuevoX;
}
