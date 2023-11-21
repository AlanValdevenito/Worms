#ifndef GRANADA_ROJA_H
#define GRANADA_ROJA_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "proyectil.h"
#include "constantes.h"

class GranadaRoja : public Proyectil
{
private:
    uint8_t potencia;
    uint16_t x;
    uint16_t y;
    uint8_t angulo;
    uint8_t tiempo;

public:
    GranadaRoja(uint8_t id, uint8_t potencia, uint8_t angulo, uint8_t tiempo, bool exploto);
    GranadaRoja(uint16_t x, uint16_t y, uint8_t angulo, bool exploto);
    ~GranadaRoja();
    uint8_t get_angulo() override;
    uint8_t get_potencia() override;
    uint8_t get_tiempo() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
};
#endif
