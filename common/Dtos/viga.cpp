#include "viga.h"

// Viga::Viga(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto) : Dto(VIGA_CODE), x(x), y(y), ancho(ancho), alto(alto) {}
Viga::Viga(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto) : x(x), y(y), ancho(ancho), alto(alto) {}

Viga::~Viga() {}

bool Viga::is_alive() { return true; }

uint16_t Viga::x_pos() { return x; }
uint16_t Viga::y_pos() { return y; }
uint16_t Viga::return_ancho() { return ancho; }
uint16_t Viga::return_alto() { return alto; }

Vigas::Vigas() : Dto(VIGA_CODE) {}
Vigas::Vigas(std::list<Viga *> vs) : Dto(VIGA_CODE), vigas(vs) {}
Vigas::~Vigas() {}

bool Vigas::is_alive() { return true; }

void *Vigas::popViga()
{
    Viga *v = vigas.front();
    vigas.pop_front();
    return v;
}

uint8_t Vigas::cantidad()
{
    return static_cast<uint8_t>(vigas.size());
}
