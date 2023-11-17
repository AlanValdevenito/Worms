#ifndef ATAQUE_AEREO_H
#define ATAQUE_AEREO_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "dto.h"
#include "proyectil.h"
#include "constantes.h"

// class AtaqueAereo : public Dto
// {
// private:
//     uint16_t x;
//     uint16_t y;
//     std::vector<std::shared_ptr<Misil>> misiles;

// public:
//     // AtaqueAereo(uint8_t id, uint16_t x, uint16_t y);
//     AtaqueAereo(uint16_t x, uint16_t y);
//     ~AtaqueAereo();
//     bool is_alive() override;
//     uint16_t x_pos() override;
//     uint16_t y_pos() override;
// };

class Misil : public Proyectil {
private:
    uint8_t id_misil;
    uint16_t x;
    uint16_t y;

public:
    Misil(uint8_t id, uint16_t x, uint16_t y);
    Misil(uint16_t x, uint16_t y);
    ~Misil();
    bool is_alive() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint8_t get_potencia() override;
    uint8_t get_tiempo() override;
    uint8_t get_angulo() override;
    // std::shared_ptr<Misil> popmisil(int i);
    // std::vector<std::shared_ptr<Misil>> return_misiles_list();
};

#endif
