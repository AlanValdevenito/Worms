#ifndef BAZUKA_H
#define BAZUKA_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "proyectil.h"
#include "constantes.h"

class Bazuka : public Proyectil
{
private:
    uint8_t potencia;
    uint16_t x;
    uint16_t y;
    uint8_t angulo;
    uint8_t direccion;

public:
    Bazuka(uint8_t id, uint8_t potencia, uint8_t angulo, bool exploto);
    Bazuka(uint16_t x, uint16_t y, uint8_t angulo, uint8_t direccion, bool exploto);
    ~Bazuka();
    uint8_t get_angulo() override;
    uint8_t get_potencia() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint8_t get_direccion();
};
#endif
