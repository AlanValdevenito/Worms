#include "gusano.h"

Gusano::Gusano(uint8_t id, uint16_t x, uint16_t y) : Dto(GUSANO_CODE), id(id), x(x), y(y) {}

Gusano::~Gusano() {}

bool Gusano::is_alive() { return true; }

uint16_t Gusano::x_pos() { return x; }

uint16_t Gusano::y_pos() { return y; }

uint8_t Gusano::get_id() { return id; }

Gusanos::Gusanos() : Dto(GUSANOS_CODE) {}
Gusanos::Gusanos(std::list<Gusano *> gs) : Dto(GUSANOS_CODE), gusanos(gs) {}
Gusanos::~Gusanos() {}

bool Gusanos::is_alive() { return true; }

Gusano *Gusanos::popGusano()
{
    Gusano *g = gusanos.front();
    gusanos.pop_front();
    return g;
}

std::list<Gusano*> Gusanos::return_gusanos_list(){ return gusanos;}

uint8_t Gusanos::cantidad()
{
    return static_cast<uint8_t>(gusanos.size());
}