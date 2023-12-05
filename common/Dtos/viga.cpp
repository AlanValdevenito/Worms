#include "viga.h"

Viga::Viga(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto, uint16_t angulo) : x(x), y(y), ancho(ancho), alto(alto), angulo(angulo) {}

Viga::~Viga() {}

bool Viga::is_alive() { return true; }

uint16_t Viga::x_pos() { return x; }
uint16_t Viga::y_pos() { return y; }
uint16_t Viga::return_ancho() { return ancho; }
uint16_t Viga::return_alto() { return alto; }
uint16_t Viga::return_angulo() { return angulo; }

Vigas::Vigas() : Dto(VIGA_CODE) {}
Vigas::Vigas(std::vector<std::shared_ptr<Viga>> vs) : Dto(VIGA_CODE), vigas(vs) {}
Vigas::~Vigas() {}

bool Vigas::is_alive() { return true; }

std::shared_ptr<Viga> Vigas::popViga(int i) { return this->vigas[i]; }

std::vector<std::shared_ptr<Viga>> Vigas::return_vigas_list() { return vigas; }

uint8_t Vigas::cantidad()
{
    return static_cast<uint8_t>(vigas.size());
}
