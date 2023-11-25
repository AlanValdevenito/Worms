#ifndef GUSANO_H
#define GUSANO_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

#include "dto.h"
#include "constantes.h"

class Gusano : public Dto
{
private:
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint8_t vida;
    uint8_t color;
    uint8_t estado;
    uint8_t arma;
    uint8_t direccion;
    uint8_t angulo;

public:
    Gusano(uint8_t id, uint16_t x, uint16_t y, uint8_t vida, uint8_t color, uint8_t estado, uint8_t arma, uint8_t dir, uint8_t angulo);
    ~Gusano();
    bool is_alive() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint8_t get_id();
    uint8_t get_vida();
    uint8_t get_color();
    uint8_t get_estado();
    uint8_t get_arma();
    uint8_t get_direccion();
    uint8_t get_angulo();
};

class Gusanos : public Dto
{
private:
    std::vector<std::shared_ptr<Gusano>> gusanos;
    uint8_t id_turno;
    bool envio_proyectil;

public:
    Gusanos();
    Gusanos(std::vector<std::shared_ptr<Gusano>> gs);
    ~Gusanos();
    bool is_alive() override;
    std::shared_ptr<Gusano> popGusano(int i);
    std::vector<std::shared_ptr<Gusano>> return_gusanos_list();
    uint8_t cantidad() override;
    uint8_t get_gusano_de_turno();
    void set_gusano_de_turno(uint8_t id);
    void set_flag_proyectil(bool estado);
    bool get_flag_proyectil();
};

#endif
