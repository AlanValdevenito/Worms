#include "fragmento.h"


Fragmento::Fragmento(uint8_t id, uint16_t x, uint16_t y, uint8_t angulo, bool exploto) : Proyectil(FRAGMENTO_CODE, id,exploto), id_fragmento(id), x(x), y(y), angulo(angulo) {}

// Fragmento::Fragmento(uint16_t x, uint16_t y,bool exploto) : Proyectil(FRAGMENTO_CODE,exploto), x(x), y(y) {}

Fragmento::~Fragmento() {}

bool Fragmento::is_alive() { return true; }

uint16_t Fragmento::x_pos() { return x; }

uint16_t Fragmento::y_pos() { return y; }

uint8_t Fragmento::get_potencia() { return 0; }

uint8_t Fragmento::get_angulo() { return 0; }

uint8_t Fragmento::get_tiempo() { return 0; }

uint8_t Fragmento::get_id() { return id_fragmento; }
