#ifndef MORTERO_H
#define MORTERO_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "proyectil.h"
#include "constantes.h"

class Mortero : public Proyectil
{
private:
    uint8_t potencia;
    uint16_t x;
    uint16_t y;
    uint8_t angulo;
    uint8_t direccion;

public:
    Mortero(uint8_t id, uint8_t potencia, uint8_t angulo, bool exploto);
    Mortero(uint16_t x, uint16_t y, uint8_t angulo, uint8_t direccion, bool exploto);
    ~Mortero();
    uint8_t get_angulo() override;
    uint8_t get_potencia() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint8_t get_direccion();
};
#endif
