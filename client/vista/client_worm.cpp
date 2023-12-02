#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

#define OFFSET 30 // Definimos un offset ya que debemos hacer un corrimiento en 'x' e 'y' ya que las fisicas modeladas con Box2D
                  // tienen el (0,0) de los cuerpos en el centro

Worm::Worm(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos, SDL2pp::Color &color, int numeroColor, float x, float y, int vida, int direccion): 
    texturas(texturas),
    sonidos(sonidos),
    animacion(this->texturas[4]), 
    estado(QUIETO),
    x(x), 
    y(y), 
    vida(vida),
    direccion(direccion),
    angulo(0),
    turno(false), 
    numeroColor(numeroColor),
    color(color),
    camara(false)
{
    this->sonido = std::make_shared<Sonido>(this->sonidos[0]);
}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void Worm::update(int it, float nuevoX, float nuevoY, int nuevaVida, int nuevaDireccion, int nuevoAngulo, bool nuevoTurno)
{

    if (this->estado == EQUIPANDO_ARMA) {
        this->animacion.update(it);
    }

    if ((nuevoX != this->x) || (nuevoY != this->y)) {

        if (this->estado != GOLPEADO) {
            this->animacion.update(it);
        }

        this->x = nuevoX;
        this->y = nuevoY;
        
    }

    this->vida = nuevaVida;
    this->direccion = nuevaDireccion;
    this->angulo = nuevoAngulo;

    if (nuevoTurno && (not this->turno)) {
        this->sonido->cambiar(this->sonidos[0]);
    }

    this->turno = nuevoTurno;
    this->camara = nuevoTurno;
}

void Worm::update_estado(SDL2pp::Renderer &renderer, int nuevoEstado, int tipoDeArma) {
    this->estado = nuevoEstado;
    this->tipoDeArma = tipoDeArma;

    if ((nuevoEstado == MOVIENDOSE) || (nuevoEstado == QUIETO)) {
        this->animacion.cambiar(this->texturas[4]);

        if (this->tipoDeArma == SIN_ARMA) {
            std::cout << "Eliminando arma del gusano cuyo ID tengo arriba\n" << std::endl;
            this->arma.reset();
        }
    }

    else if (nuevoEstado == CAYENDO) {
        this->animacion.cambiar(this->texturas[5]);
    }

    else if (nuevoEstado == SALTANDO_ADELANTE) {
        this->animacion.cambiar(this->texturas[6]);
        this->animacion.no_repetir_animacion();

        this->sonido->cambiar(this->sonidos[1]);
    }

    else if (nuevoEstado == SALTANDO_ATRAS) {
        this->animacion.cambiar(this->texturas[7]);
        this->animacion.no_repetir_animacion();

        this->sonido->cambiar(this->sonidos[2]);
    }

    else if (nuevoEstado == EQUIPANDO_ARMA) {
        equipar_arma(renderer, tipoDeArma);
    }

    else if (nuevoEstado == GOLPEADO) {
        this->animacion.cambiar(this->texturas[8]);
    }

    else if (nuevoEstado == MUERTO) {
        this->animacion.cambiar(this->texturas[9]);

        this->sonido->cambiar(this->sonidos[3]);
    }
}

void Worm::equipar_arma(SDL2pp::Renderer &renderer, int tipoDeArma) {
    this->tipoDeArma = tipoDeArma;

    if (tipoDeArma == BATE) {
        this->animacion.cambiar(this->texturas[10]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionBateDeBaseball>(renderer, this->texturas, this->sonidos);
    }

    else if (tipoDeArma == GRANADA_VERDE) {
        this->animacion.cambiar(this->texturas[11]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionGranadaVerde>(renderer, this->texturas, this->sonidos);
    }

    else if (tipoDeArma == BAZOOKA) {
        this->animacion.cambiar(this->texturas[12]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionBazooka>(renderer, this->texturas, this->sonidos);
    }

    else if (tipoDeArma == BANANA) {
        this->animacion.cambiar(this->texturas[13]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionBanana>(renderer, this->texturas, this->sonidos);
    }

    else if (tipoDeArma == GRANADA_SANTA) {
        this->animacion.cambiar(this->texturas[14]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionGranadaSanta>(renderer, this->texturas, this->sonidos);
    }

    else if (tipoDeArma == DINAMITA) {
        this->animacion.cambiar(this->texturas[15]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionDinamita>(renderer, this->texturas, this->sonidos);
    }

    else if (tipoDeArma == TELETRANSPORTACION) {
        this->animacion.cambiar(this->texturas[16]);
        this->animacion.no_repetir_animacion();
    }

    else if (tipoDeArma == ATAQUE_AEREO) {
        this->animacion.cambiar(this->texturas[17]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionAtaqueAereo>(renderer, this->texturas, this->sonidos);
    }

    else if (tipoDeArma == GRANADA_ROJA) {
        this->animacion.cambiar(this->texturas[18]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionGranadaRoja>(renderer, this->texturas, this->sonidos);
    }

    else if (tipoDeArma == MORTERO) {
        this->animacion.cambiar(this->texturas[19]);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_unique<AnimacionMortero>(renderer, this->texturas, this->sonidos);
    }
}

void Worm::render(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior)
{
    SDL_RendererFlip flip = this->direccion ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    if (this->sonido) {
        this->sonido->reproducir();
    }

    if (this->estado == MUERTO) {
        this->animacion.render(renderer, this->camara ? SDL2pp::Rect(camaraCentroX - OFFSET, y - 20 - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE) : SDL2pp::Rect(x - OFFSET - camaraLimiteIzquierdo, y - 20 - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE), flip);
        return;
    }
    
    if (this->estado == APUNTANDO) {
        int posicionX = this->camara ? (camaraCentroX - OFFSET) : (x - OFFSET - camaraLimiteIzquierdo);
        int posicionY = this->camara ? (y - OFFSET - camaraLimiteSuperior) : (y - OFFSET - camaraLimiteSuperior);
        this->arma->render(renderer, this->color, posicionX, posicionY, this->direccion);

    } else {
        this->animacion.render(renderer, this->camara ? SDL2pp::Rect(camaraCentroX - OFFSET, y - OFFSET - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE) : SDL2pp::Rect(x - OFFSET - camaraLimiteIzquierdo, y - OFFSET - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE), flip, this->angulo);
    }

    if ((this->estado == EQUIPANDO_ARMA) && (this->animacion.completa())) {
        
        if ((this->tipoDeArma != DINAMITA) && (this->tipoDeArma != TELETRANSPORTACION) && (this->tipoDeArma != ATAQUE_AEREO)) {
            this->estado = APUNTANDO;
        }
    }

    this->render_vida(renderer, camaraCentroX, camaraLimiteIzquierdo, camaraLimiteSuperior);
}

void Worm::render_arma(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {

    if ((this->arma) && (this->estado != EQUIPANDO_ARMA) && (this->estado != APUNTANDO)) {
        std::cout << "Renderizando arma del gusano cuyo ID tengo arriba\n" << std::endl;
        this->arma->render(renderer, this->color, camaraLimiteIzquierdo, camaraLimiteSuperior);
    }

}

void Worm::render_vida(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 18);
    SDL2pp::Color blanco(255, 255, 255, 255); 

    /********** BORDE **********/

    SDL2pp::Texture borde(renderer, SDL2pp::Surface(DATA_PATH "/borde.png").SetColorKey(true, 0));

    renderer.Copy(
        borde,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->camara ? (camaraCentroX + 10 - OFFSET) : (this->x - 19 - camaraLimiteIzquierdo),
                     this->camara ? (this->y - 45 - camaraLimiteSuperior) : (this->y - 45 - camaraLimiteSuperior), 
                     41, 29)
    );

    /********** CONTENEDOR **********/

    SDL2pp::Rect contenedor(this->camara ? (camaraCentroX + 13 - OFFSET) : (this->x - 16 - camaraLimiteIzquierdo),
                            this->camara ? (this->y - 42 - camaraLimiteSuperior) : (this->y - 42 - camaraLimiteSuperior), 
                            34, 22);
	renderer.SetDrawColor(this->color); 
	renderer.FillRect(contenedor);

    /********** VIDA **********/

	SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->vida), blanco);
	SDL2pp::Texture texture(renderer, surface);

    if (this->vida == 100) {
        SDL2pp::Rect mensaje(this->camara ? (camaraCentroX + 12 - OFFSET) : (this->x - 16 - camaraLimiteIzquierdo),
                            this->camara ? (this->y - 42 - camaraLimiteSuperior) : (this->y - 42 - camaraLimiteSuperior), 
                            surface.GetWidth(), surface.GetHeight());

        renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
    
    } else if ((this->vida < 100) && (this->vida >= 10)) {
        SDL2pp::Rect mensaje(this->camara ? (camaraCentroX + 17 - OFFSET) : (this->x - 11 - camaraLimiteIzquierdo),
                            this->camara ? (this->y - 42 - camaraLimiteSuperior) : (this->y - 42 - camaraLimiteSuperior), 
                            surface.GetWidth(), surface.GetHeight());

        renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
    
    } else if (this->vida < 10) {
        SDL2pp::Rect mensaje(this->camara ? (camaraCentroX + 23 - OFFSET) : (this->x - 5 - camaraLimiteIzquierdo),
                            this->camara ? (this->y - 42 - camaraLimiteSuperior) : (this->y - 42 - camaraLimiteSuperior), 
                            surface.GetWidth(), surface.GetHeight());

        renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
    }

}

/******************** ARMA ********************/

int Worm::get_tipo_de_arma() {
    return this->tipoDeArma;
}

/******************** PROYECTIL ********************/

void Worm::update_proyectil(SDL2pp::Renderer &renderer, int id, float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion, int nuevoEstado, int nuevoTiempo) {
    if (this->arma) {
        this->arma->update(nuevoX, nuevoY, nuevoEstado, nuevoAngulo, nuevaDireccion, nuevoTiempo, id);
    }
}

void Worm::set_tiempo(int tiempo) {
    this->arma->set_tiempo(tiempo);
}

int Worm::get_tiempo() {
    return this->arma->get_tiempo();
}

/******************** ANGULO ********************/

void Worm::aumentar_angulo() {
    if (this->estado == APUNTANDO) {
        this->arma->aumentar_angulo();
    }
}

void Worm::decrementar_angulo() {
    if (this->estado == APUNTANDO) {
        this->arma->decrementar_angulo();
    }
}

int Worm::get_angulo() {
    return this->arma->get_angulo();
}

/******************** POTENCIA ********************/

void Worm::aumentar_potencia() {
    if (this->estado == APUNTANDO) {
        this->arma->aumentar_potencia();
    }
}

int Worm::get_potencia() {
    if (this->estado == APUNTANDO) {
        return this->arma->get_potencia();
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

int Worm::get_estado() {
    return this->estado;
}

int Worm::get_color() {
    return this->numeroColor;
}

bool Worm::get_turno() {
    return this->turno;
}

/******************** SETTERS GENERALES ********************/

void Worm::set_turno(bool nuevoTurno) {
    this->turno = nuevoTurno;
}

void Worm::set_camara(bool nuevaCamara) {
    this->camara = nuevaCamara;
} 