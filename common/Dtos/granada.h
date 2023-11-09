#ifndef GRANADA_H
#define GRANADA_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class GranadaVerde : public Dto
{
private:
    uint8_t potencia;
    uint8_t angulo;
    // uint8_t tiempo;
    uint16_t x;
    uint16_t y;

public:
    GranadaVerde(uint8_t id ,uint8_t potencia, uint8_t angulo);
    // GranadaVerde(uint8_t id , uint16_t x, uint16_t y);
    ~GranadaVerde();
    bool is_alive() override;
    uint8_t get_angulo();
    uint8_t get_potencia();
};
#endif
