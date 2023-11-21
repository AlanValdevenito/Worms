#include "granada.h"

GranadaVerde::GranadaVerde(uint8_t id, uint8_t potencia, uint8_t angulo, uint8_t tiempo, bool exploto) : Proyectil(GRANADA_VERDE_CODE, id,exploto), potencia(potencia), angulo(angulo), tiempo(tiempo) {}

GranadaVerde::GranadaVerde(uint16_t x, uint16_t y, uint8_t angulo, bool exploto) : Proyectil(GRANADA_VERDE_CODE,exploto), x(x), y(y),angulo(angulo) {}

GranadaVerde::GranadaVerde(uint16_t x, uint16_t y, bool exploto) : Proyectil(GRANADA_VERDE_CODE,exploto), x(x), y(y),angulo(0) {}


GranadaVerde::~GranadaVerde() {}

// bool GranadaVerde::is_alive() { return true; }

uint8_t GranadaVerde::get_potencia() { return potencia; }

uint8_t GranadaVerde::get_angulo() { return angulo; }

uint8_t GranadaVerde::get_tiempo() { return tiempo; }

uint16_t GranadaVerde::x_pos() { return x; }

uint16_t GranadaVerde::y_pos() { return y; }
