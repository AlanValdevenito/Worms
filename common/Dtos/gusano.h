#ifndef GUSANO_H
#define GUSANO_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"

const uint8_t CODE_GUSANO = 2;

class Gusano : public Dto
{
private:
    uint8_t id;
    uint16_t x;
    uint16_t y;

public:
    Gusano(uint8_t id, uint16_t x, uint16_t y);
    ~Gusano();
    bool is_alive() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint8_t get_id();
};
#endif
