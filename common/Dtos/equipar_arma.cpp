#include "equipar_arma.h"

EquiparArma::EquiparArma(uint8_t id_cliente, uint8_t arma) : Dto(EQUIPAR_ARMA_CODE, id_cliente), arma(arma) {}

EquiparArma::~EquiparArma() {}

bool EquiparArma::is_alive() { return true; }

uint8_t EquiparArma::get_arma() {return arma;}
