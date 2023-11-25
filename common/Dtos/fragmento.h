#ifndef FRAGMENTO_H
#define FRAGMENTO_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "dto.h"
#include "proyectil.h"
#include "constantes.h"

class Fragmento : public Proyectil
{
private:
    uint8_t id_fragmento;
    uint16_t x;
    uint16_t y;
    uint8_t angulo;

public:
    Fragmento(uint8_t id, uint16_t x, uint16_t y, uint8_t angulo, bool exploto);
    // Fragmento(uint16_t x, uint16_t y, bool exploto);
    ~Fragmento();
    bool is_alive() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint8_t get_potencia() override;
    uint8_t get_tiempo() override;
    uint8_t get_angulo() override;
    uint8_t get_id() override;
};

#endif
