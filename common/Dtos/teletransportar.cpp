#include "teletransportar.h"

Teletransportar::Teletransportar(uint8_t id, uint16_t x, uint16_t y) : Dto(TELETRANSPORTAR_CODE, id), x(x),y(y) {}

Teletransportar::~Teletransportar() {}

bool Teletransportar::is_alive() { return true; }

uint16_t Teletransportar::x_pos() { return x; }

uint16_t Teletransportar::y_pos() { return y; }
