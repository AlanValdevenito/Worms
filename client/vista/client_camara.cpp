#include "client_camara.h"

#include <iostream>

Camara::Camara(float ventanaAncho, float ventanaAlto): x(0), y(0), ancho(ventanaAncho), alto(ventanaAlto) {}


void Camara::seguirWorm(Worm &worm) {
    this->x = worm.get_x() / 24;
    this->y = worm.get_y() / 24;
}

bool Camara::comprobarRenderizado(float objetoX, float objetoY, float objetoAncho, float objetoAlto) {
    // Calculamos los limites de la camara
    /*float izquierda = this->x - ((this->ancho/2) / 24);
    float derecha = this->x + ((this->ancho/2) / 24);
    float arriba = this->y - ((this->alto/2) / 24);
    float abajo = this->y + ((this->alto/2) / 24);

    // std::cout << objetoX << " " << derecha << std::endl;
    // std::cout << objetoX << " " << izquierda << std::endl;
    // std::cout << objetoY << " " << abajo << std::endl;
    // std::cout << objetoY << " " << arriba << std::endl;

    return ((objetoX <= derecha) && (objetoX >= izquierda) && (objetoY <= abajo) && (objetoY >= arriba));*/

    return true;
}

void Camara::update() {}