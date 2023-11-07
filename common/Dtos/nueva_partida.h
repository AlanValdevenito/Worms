#ifndef NUEVA_PARTIDA_H
#define NUEVA_PARTIDA_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class NuevaPartida : public Dto
{
private:
    uint8_t jugadores;

public:
    NuevaPartida(uint8_t cantidad);
    ~NuevaPartida();
    bool is_alive() override;
    uint8_t get_cantidad_de_jugadores();
};
#endif