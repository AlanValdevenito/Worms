#ifndef GUSANO_H
#define GUSANO_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "dto.h"
#include "constantes.h"

class Gusano : public Dto
{
private:
    uint8_t id;
    uint16_t x;
    uint16_t y;

public:
    Gusano(uint8_t id, uint16_t x, uint16_t y);
    ~Gusano();
    bool is_alive() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint8_t get_id();
};


class Gusanos : public Dto
{
private:
    std::list<Gusano *> gusanos;

public:
    Gusanos();
    Gusanos(std::list<Gusano *> gs);
    ~Gusanos();
    bool is_alive() override;
    Gusano *popGusano();
    std::list<Gusano*> return_gusanos_list();
    uint8_t cantidad() override;
};

#endif
