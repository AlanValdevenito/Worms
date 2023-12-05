#include "bazuka.h"

Bazuka::Bazuka(uint8_t id, uint8_t potencia, uint8_t angulo, bool exploto) : Proyectil(BAZUKA_CODE, id, exploto), potencia(potencia), angulo(angulo) {}

Bazuka::Bazuka(uint16_t x, uint16_t y, uint8_t angulo, uint8_t direccion, bool exploto) : Proyectil(BAZUKA_CODE, exploto), x(x), y(y), angulo(angulo), direccion(direccion) {}

Bazuka::~Bazuka() {}

uint8_t Bazuka::get_potencia() { return potencia; }

uint8_t Bazuka::get_angulo() { return angulo; }

uint8_t Bazuka::get_direccion() { return direccion; }

uint16_t Bazuka::x_pos() { return x; }

uint16_t Bazuka::y_pos() { return y; }
