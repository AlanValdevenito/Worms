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
                                                                                          color(color),
                                                                                          turno(false),
                                                                                          configuraciones(YAML::LoadFile("/configuracion.yml")) {}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos. Esto les va a resultar muy util.

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void Worm::update(int it, float nuevoX, float nuevoY, int nuevaVida)
{

    if (this->armaEquipada) {
        this->arma.update(it);
    }

    if ((nuevoX != this->x) || (nuevoY != this->y)) {

        this->animacion.update(it);

        if (nuevoX > this->x) {
            mirar_derecha();
        
        } else if (nuevoX < this->x) {
            mirar_izquierda();
        }

        this->x = nuevoX;
        this->y = nuevoY;
        this->vida = nuevaVida;
    }
}

void Worm::render(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior)
{
    SDL_RendererFlip flip = this->mirandoIzquierda ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    if (this->armaEquipada) {
        this->arma.render(renderer, this->turno ? (camaraCentroX - OFFSET_X) : (x - OFFSET_X - camaraLimiteIzquierdo),
                          this->turno ? (y - OFFSET_Y - camaraLimiteSuperior) : (y - OFFSET_Y - camaraLimiteSuperior), this->mirandoIzquierda);
    } else {
        this->animacion.render(renderer, this->turno ? SDL2pp::Rect(camaraCentroX - OFFSET_X, y - OFFSET_Y - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE) : SDL2pp::Rect(x - OFFSET_X - camaraLimiteIzquierdo, y - OFFSET_Y - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE), flip);
    }
    
    this->render_vida(renderer, camaraCentroX, camaraLimiteIzquierdo, camaraLimiteSuperior);
}

void Worm::render_vida(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    // Cargamos la fuente de la letra
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 14);
    SDL2pp::Color blanco(255, 255, 255, 255); 

    SDL2pp::Texture borde(renderer, SDL2pp::Surface(DATA_PATH "/borde.png").SetColorKey(true, 0));

    renderer.Copy(
        borde,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->turno ? (camaraCentroX + 10 - OFFSET_X) : (this->x - 19 - camaraLimiteIzquierdo),
                     this->turno ? (this->y - 30 - camaraLimiteSuperior) : (this->y - 30 - camaraLimiteSuperior), 
                     35, 25)
    );

    SDL2pp::Rect contenedor(this->turno ? (camaraCentroX + 13 - OFFSET_X) : (this->x - 16 - camaraLimiteIzquierdo),
                            this->turno ? (this->y - 27 - camaraLimiteSuperior) : (this->y - 27 - camaraLimiteSuperior), 
                            28, 18);
	renderer.SetDrawColor(this->color); 
	renderer.FillRect(contenedor);

	SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->vida), blanco);
	SDL2pp::Texture texture(renderer, surface);

    SDL2pp::Rect mensaje(this->turno ? (camaraCentroX + 13 - OFFSET_X) : (this->x - 16 - camaraLimiteIzquierdo),
                         this->turno ? (this->y - 27 - camaraLimiteSuperior) : (this->y - 27 - camaraLimiteSuperior), 
                         surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
}

/******************** ANIMACION ********************/

void Worm::cambiar_animacion(std::string &ruta) {
    this->animacion.cambiar(ruta);
}

/******************** TURNO ********************/

void Worm::cambiar_turno() {
    this->turno = false;
    desequipar_arma();
}

void Worm::turno_actual() {
    this->turno = true;
}

/******************** DIRECCION ********************/

void Worm::mirar_derecha() {
    this->mirandoIzquierda = false;
}

void Worm::mirar_izquierda() {
    this->mirandoIzquierda = true;
}

/******************** ARMA ********************/

void Worm::equipar_arma(int tipo) {
    std::string sprite_worm = configuraciones["armas"][tipo]["sprite_worm"].as<std::string>();
    std::string sprite_apuntado = configuraciones["armas"][tipo]["sprite_apuntado"].as<std::string>();

    this->arma.equipar_arma(tipo, sprite_worm, sprite_apuntado);
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
