#include "mortero.h"


Mortero::Mortero(uint8_t id, uint8_t potencia, uint8_t angulo, bool exploto) : Proyectil(MORTERO_CODE, id, exploto), potencia(potencia), angulo(angulo) {}

Mortero::Mortero(uint16_t x, uint16_t y, uint8_t angulo, uint8_t direccion, bool exploto) : Proyectil(MORTERO_CODE,exploto), x(x), y(y), angulo(angulo), direccion(direccion) {}

Mortero::~Mortero() {}


uint8_t Mortero::get_potencia() { return potencia; }

uint8_t Mortero::get_angulo() { return angulo; }

uint8_t Mortero::get_direccion() { return direccion; }

uint16_t Mortero::x_pos() { return x; }

uint16_t Mortero::y_pos() { return y; }
