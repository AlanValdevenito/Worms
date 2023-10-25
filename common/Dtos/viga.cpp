#include "viga.h"

Viga::Viga(uint8_t x, uint8_t y, uint8_t ancho, uint8_t alto) : Dto(VIGA_CODE), x(x), y(y), ancho(ancho), alto(alto) {}

Viga::~Viga() {}

bool Viga::is_alive() { return true; }

uint8_t Viga::x_pos() { return x; }
uint8_t Viga::y_pos() { return y; }
