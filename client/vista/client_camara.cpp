#include "client_camara.h"

#include <iostream>

Camara::Camara(float ventanaAncho, float ventanaAlto): x(0), y(0), ancho(ventanaAncho), alto(ventanaAlto), moverCamara(false) {}

void Camara::seguirWorm(std::map<int, Worm *> &worms) {

    for (const auto &elemento : worms)
    {
        elemento.second->set_camara(false);

        // int estado = elemento.second->get_estado();
        bool turno = elemento.second->get_turno();

        if (turno && not this->moverCamara) {
            seguir(elemento.second->get_x(), elemento.second->get_y());
            elemento.second->set_camara(true);
        }
    }

}

void Camara::seguir(float nuevoX, float nuevoY) {
    this->x = nuevoX / 24;
    this->y = nuevoY / 24;
}

void Camara::mover(float moverX, float moverY) {

    if (this->moverCamara) {
        this->x += moverX;
        this->y += moverY;
    }
}

float Camara::getLimiteDerecho() {
    return this->x + ((this->ancho/2) / 24);
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
 