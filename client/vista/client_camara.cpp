#include "client_camara.h"

#include <iostream>

Camara::Camara(float ventanaAncho, float ventanaAlto): x(0), y(0), ancho(ventanaAncho), alto(ventanaAlto) {}


void Camara::seguirWorm(Worm &worm) {
    this->x = worm.get_x() / 24;
    this->y = worm.get_y() / 24;

    // worm.set_x(this->ancho/2);
}

bool Camara::comprobarRenderizado(float objetoX, float objetoY, float objetoAncho, float objetoAlto) {

    // Calculamos los limites de la camara
    /*float izquierda = this->x - ((this->ancho/2) / 24);
    float derecha = this->x + ((this->ancho/2) / 24);
    float arriba = this->y - ((this->alto/2) / 24);
    float abajo = this->y + ((this->alto/2) / 24);

    return ((objetoX - objetoAncho <= derecha) && (objetoX + objetoAncho >= izquierda) && (objetoY - objetoAlto/2 <= abajo) && (objetoY + objetoAlto/2 >= arriba));*/

    return true;
}

float Camara::getLimiteIzquierdo() {
    return this->x - ((this->ancho/2) / 24);
}

float Camara::get_centro_x() {
    return this->ancho/2;
}
