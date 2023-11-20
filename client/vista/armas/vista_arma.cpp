#include "vista_arma.h"

Arma::Arma(int estadoInicial): x(0), y(0), estado(estadoInicial){}

Arma::~Arma() {}

/******************** ESTADO ********************/

int Arma::get_estado() {
    return this->estado;
}

/******************** TIEMPO ********************/

void Arma::set_tiempo(int tiempoElegido) {
    // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

int Arma::get_tiempo() {
    return 0; // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

/******************** ANGULO ********************/

void Arma::aumentar_angulo() {
    // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

void Arma::decrementar_angulo() {
    // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

int Arma::get_angulo() {
    return 0; // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

/******************** POTENCIA ********************/

void Arma::aumentar_potencia() {
    // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}

int Arma::get_potencia() {
    return 0; // La implementacion le corresponde a la clase derivada (solo en caso de necesitarla)
}
