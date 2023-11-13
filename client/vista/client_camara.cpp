#include "client_camara.h"

#include <iostream>

Camara::Camara(float ventanaAncho, float ventanaAlto): x(0), y(0), ancho(ventanaAncho), alto(ventanaAlto) {}

void Camara::seguirWorm(Worm &worm) {
    this->x = worm.get_x() / 24;
    this->y = worm.get_y() / 24;
}

bool Camara::comprobarRenderizado(float objetoX, float objetoY, float objetoAncho, float objetoAlto) {

    // Calculamos los limites de la camara
    float izquierda = this->x - ((this->ancho/2) / 24);
    float derecha = this->x + ((this->ancho/2) / 24);
    float superior = this->y - ((this->alto/2) / 24);
    float inferior = this->y + ((this->alto/2) / 24);

    return ((objetoX - objetoAncho/2 <= derecha) && (objetoX + objetoAncho/2 >= izquierda) && (objetoY - objetoAlto/2 <= inferior) && (objetoY + objetoAlto/2 >= superior));
}

float Camara::getLimiteIzquierdo() {
    return this->x - ((this->ancho/2) / 24);
}
float Camara::getLimiteSuperior() {
    return this->y - ((this->alto/2) / 24);
}

float Camara::getCentroX() {
    return this->ancho/2;
}

void Camara::setDimensiones(float ventanaAncho, float ventanaAlto) {
    this->ancho = ventanaAncho;
    this->alto = ventanaAlto;
}
