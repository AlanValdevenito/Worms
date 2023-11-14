#ifndef TELETRASNPORTAR_H
#define TELETRASNPORTAR_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class Teletransportar : public Dto
{
private:
    uint8_t id_gusano;
    uint16_t x;
    uint16_t y;

public:
    Teletransportar(uint8_t id, uint16_t x, uint16_t y);
    ~Teletransportar();
    bool is_alive() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
};
#endif
