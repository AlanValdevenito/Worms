#include "saltar.h"

Saltar::Saltar(uint8_t id) : Dto(SALTAR_CODE, id) {}

Saltar::~Saltar() {}

bool Saltar::is_alive() { return true; }