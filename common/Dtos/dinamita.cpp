#include "dinamita.h"

Dinamita::Dinamita(uint8_t id, uint8_t tiempo) : Proyectil(DINAMITA_CODE, id), tiempo(tiempo) {}

Dinamita::Dinamita(uint16_t x, uint16_t y) : Proyectil(DINAMITA_CODE), x(x), y(y) {}

Dinamita::~Dinamita() {}

// bool Dinamita::is_alive() { return true; }

uint8_t Dinamita::get_potencia() { return 0; }

uint8_t Dinamita::get_angulo() { return 0; }

uint8_t Dinamita::get_tiempo() { return tiempo; }

uint16_t Dinamita::x_pos() { return x; }

uint16_t Dinamita::y_pos() { return y; }
