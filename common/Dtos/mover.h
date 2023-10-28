#ifndef MOVER_H
#define MOVER_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"

const uint8_t CODE_MOVER_A_DERECHA = 3;

class MoverADerecha : public Dto
{
private:
    uint8_t id_gusano;

public:
    MoverADerecha();
    ~MoverADerecha();
    bool is_alive() override;
    // uint8_t get_id();
};
#endif
