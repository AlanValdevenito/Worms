#include "animacion_arma.h"

AnimacionArma::AnimacionArma(int estadoInicial): x(0), y(0), estado(estadoInicial){}

AnimacionArma::~AnimacionArma() {}

/******************** ESTADO ********************/

int AnimacionArma::get_estado() {
    return this->estado;
}

/******************** TIEMPO ********************/

void AnimacionArma::set_tiempo(int tiempoElegido) {
    // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

int AnimacionArma::get_tiempo() {
    return 0; // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

/******************** ANGULO ********************/

void AnimacionArma::aumentar_angulo() {
    // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

void AnimacionArma::decrementar_angulo() {
    // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

int AnimacionArma::get_angulo() {
    return 0; // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

/******************** POTENCIA ********************/

void AnimacionArma::aumentar_potencia() {
    // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

int AnimacionArma::get_potencia() {
    return 0; // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}
