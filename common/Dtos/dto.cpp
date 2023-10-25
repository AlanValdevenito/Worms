#include "dto.h"

Dto::Dto() {}

Dto::Dto(uint8_t code) : code(code) {}

Dto::~Dto() {}

uint8_t Dto::return_code() { return code; }

uint8_t Dto::orientation() { return 1; }

std::string Dto::return_line() { return VACIO; }

bool Dto::is_alive() { return true; }

uint8_t Dto::x_pos() { return 0; }
uint8_t Dto::y_pos() { return 0; }
