#include "ganador.h"

Ganador::Ganador(uint8_t id) : Dto(GANADOR_CODE,id), id_ganador(id) {}

Ganador::~Ganador() {}

bool Ganador::is_alive() { return true; }