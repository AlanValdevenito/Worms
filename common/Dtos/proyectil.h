#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "dto.h"
#include "constantes.h"

class Proyectil : public Dto
{
private:
    bool exploto;

public:
    Proyectil(uint8_t code, bool exploto = false);
    Proyectil(uint8_t code, uint8_t id, bool exploto = false);
    ~Proyectil();
    bool is_alive() override;
    virtual uint8_t get_angulo() = 0;
    virtual uint8_t get_potencia() = 0;
    virtual uint8_t get_tiempo();
    virtual uint8_t get_direccion();
    virtual uint16_t x_pos() = 0;
    virtual uint16_t y_pos() = 0;
    virtual uint8_t get_id();
    virtual bool get_exploto();
    virtual void set_exploto(bool estado);
};

class Proyectiles : public Dto
{
private:
    std::vector<std::shared_ptr<Proyectil>> proyectiles;

public:
    Proyectiles();
    Proyectiles(std::vector<std::shared_ptr<Proyectil>> p);
    ~Proyectiles();
    bool is_alive() override;
    std::shared_ptr<Proyectil> popProyectil(int i);
    std::vector<std::shared_ptr<Proyectil>> return_proyectiles();
    uint8_t cantidad() override;
};
#endif
