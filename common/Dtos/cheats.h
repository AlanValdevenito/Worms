#ifndef CHEAT_H
#define CHEAT_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "dto.h"
#include "constantes.h"

class Cheat : public Dto
{
private:
    uint8_t cheat;

public:
    Cheat(uint8_t id, uint8_t code);
    ~Cheat();
    bool is_alive() override;
    uint8_t get_cheat();
};
#endif
