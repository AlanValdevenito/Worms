#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"

const uint8_t POS_CODE = 5;

class Position : public Dto
{
private:
    uint8_t x;
    uint8_t y;

public:
    Position(uint8_t x, uint8_t y);
    ~Position();
    bool is_alive() override;
    uint8_t x_pos() override;
    uint8_t y_pos() override;
};
#endif
