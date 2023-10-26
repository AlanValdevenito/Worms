#include "position.h"

Position::Position(uint8_t x, uint8_t y) : Dto(POS_CODE), x(x), y(y) {}

Position::~Position() {}

bool Position::is_alive() { return true; }
// uint8_t Position::x_pos() { return x; }
// uint8_t Position::y_pos() { return y; }