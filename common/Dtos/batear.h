#ifndef BATEAR_H
#define BATEAR_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class Batear : public Dto
{
private:
    uint8_t angulo;

public:
    Batear(uint8_t id ,uint8_t angulo);
    ~Batear();
    bool is_alive() override;
    uint8_t get_angulo();
};
#endif
