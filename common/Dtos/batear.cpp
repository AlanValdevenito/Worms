#include "batear.h"

Batear::Batear(uint8_t id, uint8_t angulo) : Dto(BATEAR_CODE, id), angulo(angulo) {}

Batear::~Batear() {}

bool Batear::is_alive() { return true; }

uint8_t Batear::get_angulo() { return angulo; }


// MoverAIzquierda::MoverAIzquierda(uint8_t id) : Dto(MOVER_A_IZQUIERDA_CODE, id) {}

// MoverAIzquierda::~MoverAIzquierda() {}

// bool MoverAIzquierda::is_alive() { return true; }