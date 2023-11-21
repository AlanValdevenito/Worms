#ifndef SALTAR_H
#define SALTAR_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class Saltar : public Dto
{
private:
    uint8_t id_gusano;
    uint8_t direccion;

public:
    Saltar(uint8_t id, uint8_t direccion);
    ~Saltar();
    bool is_alive() override;
    uint8_t get_direccion();
};
#endif