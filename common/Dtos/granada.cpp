#include "granada.h"

GranadaVerde::GranadaVerde(uint8_t id, uint8_t potencia, uint8_t angulo) : Dto(GRANADA_VERDE_CODE, id), potencia(potencia),angulo(angulo) {}
// GranadaVerde::GranadaVerde(uint8_t id, , uint16_t x, uint16_t y) : Dto(GRANADA_VERDE_CODE, id), x(x),y(y) {}

GranadaVerde::~GranadaVerde() {}

bool GranadaVerde::is_alive(){return true;}

uint8_t GranadaVerde::get_potencia() { return potencia; }
uint8_t GranadaVerde::get_angulo() { return angulo; }
// uint8_t GranadaVerde::get_tiempo() { return angulo; }

