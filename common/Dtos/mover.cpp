#include "mover.h"

MoverADerecha::MoverADerecha(uint8_t id) : Dto(MOVER_A_DERECHA_CODE, id) {}

MoverADerecha::~MoverADerecha() {}

bool MoverADerecha::is_alive() { return true; }

MoverAIzquierda::MoverAIzquierda(uint8_t id) : Dto(MOVER_A_IZQUIERDA_CODE, id) {}

MoverAIzquierda::~MoverAIzquierda() {}

bool MoverAIzquierda::is_alive() { return true; }
