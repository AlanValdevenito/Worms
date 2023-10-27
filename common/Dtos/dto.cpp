#include "dto.h"

Dto::Dto() {}

Dto::Dto(uint8_t code) : code(code) {}

Dto::~Dto() {}

uint8_t Dto::return_code() { return code; }

uint8_t Dto::orientation() { return 1; }

std::string Dto::return_line() { return VACIO; }

bool Dto::is_alive() { return true; }

uint16_t Dto::x_pos() { return 0; }
uint16_t Dto::y_pos() { return 0; }
uint16_t Dto::return_alto() { return 0; }
uint16_t Dto::return_ancho() { return 0; }

void *Dto::popViga() { return nullptr; }

uint8_t Dto::cantidad() { return 0; }