#include "proyectil.h"

Proyectil::Proyectil(uint8_t code) : Dto(code) {}

Proyectil::Proyectil(uint8_t code, uint8_t id) : Dto(code, id){}

Proyectil::~Proyectil(){}

bool Proyectil::is_alive(){return true;}

uint8_t Proyectil::get_tiempo(){return 0;}
