#include "saltar.h"

Saltar::Saltar(uint8_t id, uint8_t direccion) : Dto(SALTAR_CODE, id), direccion(direccion) {}

Saltar::~Saltar() {}

bool Saltar::is_alive() { return true; }

uint8_t Saltar::get_direccion() { return direccion; }
