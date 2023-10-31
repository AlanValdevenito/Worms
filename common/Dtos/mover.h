#ifndef MOVER_H
#define MOVER_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class MoverADerecha : public Dto
{
private:
    uint8_t id_gusano;

public:
    MoverADerecha(uint8_t id);
    ~MoverADerecha();
    bool is_alive() override;
    // uint8_t get_id();
};

class MoverAIzquierda : public Dto
{
private:
    uint8_t id_gusano;

public:
    MoverAIzquierda(uint8_t id);
    ~MoverAIzquierda();
    bool is_alive() override;
    // uint8_t get_id();
};
#endif
