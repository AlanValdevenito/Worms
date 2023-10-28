#include "gusano.h"

Gusano::Gusano(uint8_t id, uint16_t x, uint16_t y) : Dto(GUSANO_CODE), id(id), x(x), y(y) {}

Gusano::~Gusano() {}

bool Gusano::is_alive() { return true; }

uint16_t Gusano::x_pos() { return x; }

uint16_t Gusano::y_pos() { return y; }

uint8_t Gusano::get_id() { return id; }
