#ifndef VIGA_H
#define VIGA_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"

const uint8_t VIGA_CODE = 6; // CAMBIAR

class Viga : public Dto
{
private:
    uint8_t x;
    uint8_t y;
    uint8_t ancho;
    uint8_t alto;

public:
    Viga(uint8_t x, uint8_t y, uint8_t ancho, uint8_t alto);
    ~Viga();
    bool is_alive() override;
    uint8_t x_pos() override;
    uint8_t y_pos() override;
};
#endif