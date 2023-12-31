#include "granada_santa.h"

GranadaSanta::GranadaSanta(uint8_t id, uint8_t potencia, uint8_t angulo, uint8_t tiempo) : Proyectil(GRANADA_SANTA_CODE, id, false), potencia(potencia), angulo(angulo), tiempo(tiempo) {}

GranadaSanta::GranadaSanta(uint16_t x, uint16_t y, uint8_t angulo, bool exploto, uint8_t tiempo) : Proyectil(GRANADA_SANTA_CODE, exploto), x(x), y(y), angulo(angulo), tiempo(tiempo) {}

GranadaSanta::~GranadaSanta() {}

uint8_t GranadaSanta::get_potencia() { return potencia; }

uint8_t GranadaSanta::get_angulo() { return angulo; }

uint8_t GranadaSanta::get_tiempo() { return tiempo; }

uint16_t GranadaSanta::x_pos() { return x; }

uint16_t GranadaSanta::y_pos() { return y; }
