#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class Proyectil : public Dto
{
private:

public:
    Proyectil(uint8_t code);
    Proyectil(uint8_t code, uint8_t id);
    ~Proyectil();
    bool is_alive() override;
    virtual uint8_t get_angulo()=0;
    virtual uint8_t get_potencia()=0;
    virtual uint8_t get_tiempo();
    virtual uint8_t get_direccion() = 0;
    virtual uint16_t x_pos()=0;
    virtual uint16_t y_pos()=0;
};
#endif
