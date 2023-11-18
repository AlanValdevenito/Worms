#include "ataque_aereo.h"

Misil::Misil(uint8_t id, uint16_t x, uint16_t y) : Proyectil(ATAQUE_AEREO_CODE, id), id_misil(id), x(x), y(y) {}

Misil::Misil(uint16_t x, uint16_t y) : Proyectil(ATAQUE_AEREO_CODE), x(x), y(y) {}

Misil::~Misil() {}

bool Misil::is_alive() { return true; }

uint16_t Misil::x_pos() { return x; }

uint16_t Misil::y_pos() { return y; }

uint8_t Misil::get_potencia() { return 0; }

uint8_t Misil::get_angulo() { return 0; }

uint8_t Misil::get_tiempo() { return 0; }
