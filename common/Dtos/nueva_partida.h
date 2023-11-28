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
    uint8_t mapa;

public:
    NuevaPartida(uint8_t cantidad, uint8_t mapa);
    ~NuevaPartida();
    bool is_alive() override;
    uint8_t get_cantidad_de_jugadores();
    uint8_t get_mapa();
};
#endif