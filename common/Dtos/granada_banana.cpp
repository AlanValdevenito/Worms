#include "granada_banana.h"

GranadaBanana::GranadaBanana(uint8_t id, uint8_t potencia, uint8_t angulo, uint8_t tiempo) : Proyectil(GRANADA_BANANA_CODE, id), potencia(potencia), angulo(angulo), tiempo(tiempo) {}

GranadaBanana::GranadaBanana(uint16_t x, uint16_t y) : Proyectil(GRANADA_BANANA_CODE), x(x), y(y), angulo(0) {}

GranadaBanana::~GranadaBanana() {}

// bool GranadaBanana::is_alive() { return true; }

uint8_t GranadaBanana::get_potencia() { return potencia; }

uint8_t GranadaBanana::get_angulo() { return angulo; }

uint8_t GranadaBanana::get_tiempo() { return tiempo; }

uint16_t GranadaBanana::x_pos() { return x; }

uint16_t GranadaBanana::y_pos() { return y; }
