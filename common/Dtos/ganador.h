#ifndef GANADOR_H
#define GANADOR_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class Ganador : public Dto
{
private:
    uint8_t id_ganador;
public:
    Ganador(uint8_t id);
    ~Ganador();
    bool is_alive() override;
};
#endif