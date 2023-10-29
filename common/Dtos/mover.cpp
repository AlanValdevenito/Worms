#include "mover.h"

MoverADerecha::MoverADerecha() : Dto(MOVER_A_DERECHA_CODE) {}

MoverADerecha::~MoverADerecha() {}

bool MoverADerecha::is_alive() { return true; }



// uint8_t Gusano::get_id() { return id_gusano; }

MoverAIzquierda::MoverAIzquierda() : Dto(MOVER_A_IZQUERDA_CODE) {}

MoverAIzquierda::~MoverAIzquierda() {}

bool MoverAIzquierda::is_alive() { return true; }