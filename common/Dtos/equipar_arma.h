#ifndef EQUIPAR_ARMA_H
#define EQUIPAR_ARMA_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class EquiparArma : public Dto
{
private:
    uint8_t arma;

public:
    EquiparArma(uint8_t id_cliente, uint8_t arma);
    ~EquiparArma();
    bool is_alive() override;
    uint8_t get_arma();
};
#endif