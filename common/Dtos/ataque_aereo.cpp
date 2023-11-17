#include "ataque_aereo.h"

// AtaqueAereo::AtaqueAereo(uint16_t x, uint16_t y): Dto(ATAQUE_AEREO_CODE),x(x), y(x){}

// AtaqueAereo::AtaqueAereo(std::vector<std::shared_ptr<Misil>> ms): Dto(ATAQUE_AEREO_CODE),misiles(ms){}

// AtaqueAereo::~AtaqueAereo(){}

// bool AtaqueAereo::is_alive(){return true;}

// uint16_t AtaqueAereo::x_pos(){return x;}

// uint16_t AtaqueAereo::y_pos(){return y;}


// std::shared_ptr<Misil> Misil::popmisil(int i)
// {
//     return this->misiles[i];
// }

// std::vector<std::shared_ptr<Misil>> Misil::return_misil_list() { return misil; }


Misil::Misil(uint8_t id, uint16_t x, uint16_t y): Proyectil(ATAQUE_AEREO_CODE,id), id_misil(id),x(x),y(y) {}
Misil::Misil( uint16_t x, uint16_t y): Proyectil(ATAQUE_AEREO_CODE),x(x),y(y) {}

Misil::~Misil(){}

bool Misil::is_alive(){return true;}

uint16_t Misil::x_pos(){return x;}

uint16_t Misil::y_pos(){return y;}
uint8_t Misil::get_potencia() { return 0; }

uint8_t Misil::get_angulo() { return 0; }

uint8_t Misil::get_tiempo() { return 0; }