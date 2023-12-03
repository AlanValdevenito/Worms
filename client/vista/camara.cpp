#include "camara.h"

#include <iostream>

#define LIMITE_X 12
#define LIMITE_Y 20

Camara::Camara(float ventanaAncho, float ventanaAlto): x(0), y(0), ancho(ventanaAncho), alto(ventanaAlto), moverCamara(false) {}

void Camara::seguirWorm(std::map<int, AnimacionWorm*> &worms) {

    for (const auto &elemento : worms)
    {
        elemento.second->set_camara(false);
    }
    
    for (const auto &elemento : worms)
    {
        int estado = elemento.second->get_estado();
        bool turno = elemento.second->get_turno();

        if (estado == MUERTO) {
            continue;
        }

        if ((not turno) && (estado != QUIETO) && not this->moverCamara) {
            seguir(elemento.second->get_x(), elemento.second->get_y());
            elemento.second->set_camara(true);
            break;
        }

        else if (turno && (estado != QUIETO) && not this->moverCamara) {
            seguir(elemento.second->get_x(), elemento.second->get_y());
            elemento.second->set_camara(true);
            break;
        }
    }

}

void Camara::seguir(float nuevoX, float nuevoY) {
    this->x = nuevoX / 24;
    this->y = nuevoY / 24;
}

void Camara::mover(float moverX, float moverY) {

    if (this->moverCamara) {

        if (((this->x + moverX) < LIMITE_X) || ((this->y + moverY) > LIMITE_Y)) {
            return;
        }

        this->x += moverX;
        this->y += moverY;
    }
}

bool Camara::comprobarRenderizado(float objetoX, float objetoY, float objetoAncho, float objetoAlto) {
    float limiteIzquierda = getLimiteIzquierdo();
    float limiteDerecho = getLimiteDerecho();
    float limiteSuperior = getLimiteSuperior();
    float limiteInferior = getLimiteInferior();

    return ((objetoX <= (limiteDerecho + objetoAncho)) && (objetoX >= (limiteIzquierda - objetoAncho)) && (objetoY >= (limiteSuperior - objetoAlto)) && (objetoY <= (limiteInferior + objetoAlto)));
}

float Camara::getLimiteDerecho() {
    return this->x + ((this->ancho/2) / 24); // Metros
}

float Camara::getLimiteIzquierdo() {
    return this->x - ((this->ancho/2) / 24);
}

float Camara::getLimiteSuperior() {
    return this->y - ((this->alto/2) / 24);
}

float Camara::getLimiteInferior() {
    return this->y + ((this->alto/2) / 24);
}

float Camara::getCentroX() {
    return this->ancho/2;
}

void Camara::setDimensiones(float ventanaAncho, float ventanaAlto) {
    this->ancho = ventanaAncho;
    this->alto = ventanaAlto;
}

void Camara::setMoverCamara(bool nuevoMover) {
    this->moverCamara = nuevoMover;
}
 