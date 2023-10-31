#ifndef VIGA_H
#define VIGA_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "dto.h"
#include "constantes.h"

class Viga : public Dto
{
private:
    uint16_t x;
    uint16_t y;
    uint16_t ancho;
    uint16_t alto;

public:
    Viga(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto);
    ~Viga();
    bool is_alive() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint16_t return_ancho() override;
    uint16_t return_alto() override;
};

class Vigas : public Dto
{
private:
    std::list<Viga *> vigas;

public:
    Vigas();
    Vigas(std::list<Viga *> vs);
    ~Vigas();
    bool is_alive() override;
    void *popViga() override;
    uint8_t cantidad() override;
    std::list<Viga*> return_vigas_list();
};
#endif
