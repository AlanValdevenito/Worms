#include "granada_roja.h"

GranadaRoja::GranadaRoja(uint8_t id, uint8_t potencia, uint8_t angulo, uint8_t tiempo, bool exploto) : Proyectil(GRANADA_ROJA_CODE, id,exploto), potencia(potencia), angulo(angulo), tiempo(tiempo) {}

GranadaRoja::GranadaRoja(uint16_t x, uint16_t y, uint8_t angulo, bool exploto) : Proyectil(GRANADA_ROJA_CODE,exploto), x(x), y(y), angulo(angulo) {}

GranadaRoja::~GranadaRoja() {}

uint8_t GranadaRoja::get_potencia() { return potencia; }

uint8_t GranadaRoja::get_angulo() { return angulo; }

uint8_t GranadaRoja::get_tiempo() { return tiempo; }

uint16_t GranadaRoja::x_pos() { return x; }

uint16_t GranadaRoja::y_pos() { return y; }
