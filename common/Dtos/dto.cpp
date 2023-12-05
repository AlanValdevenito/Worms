#include "dto.h"

Dto::Dto() {}

Dto::Dto(uint8_t code) : code(code), id_cliente(0) {}

Dto::Dto(uint8_t code, uint8_t id) : code(code), id_cliente(id) {}

Dto::~Dto() {}

uint8_t Dto::return_code() { return code; }

uint8_t Dto::orientation() { return 1; }

std::string Dto::return_line() { return VACIO; }

bool Dto::is_alive() { return true; }

uint16_t Dto::x_pos() { return 0; }

uint16_t Dto::y_pos() { return 0; }

uint16_t Dto::return_alto() { return 0; }

uint16_t Dto::return_ancho() { return 0; }

uint16_t Dto::return_angulo() { return 0; }

uint8_t Dto::cantidad() { return 0; }

uint8_t Dto::get_cliente_id() { return id_cliente; }
