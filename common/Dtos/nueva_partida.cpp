#include "nueva_partida.h"

NuevaPartida::NuevaPartida(uint8_t cantidad) : Dto(NUEVA_PARTIDA_CODE), jugadores(cantidad) {}

NuevaPartida::~NuevaPartida() {}

bool NuevaPartida::is_alive() { return true; }

uint8_t NuevaPartida::get_cantidad_de_jugadores() { return jugadores; }