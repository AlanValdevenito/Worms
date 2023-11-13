#ifndef DINAMITA_H
#define DINAMITA_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "proyectil.h"
#include "constantes.h"

class Dinamita : public Proyectil
{
private:
    uint16_t x;
    uint16_t y;
    uint8_t tiempo;

public:
    Dinamita(uint8_t id, uint8_t tiempo);
    Dinamita(uint16_t x, uint16_t y);
    ~Dinamita();
    uint8_t get_angulo() override;
    uint8_t get_potencia() override;
    uint8_t get_tiempo() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
};
#endif
