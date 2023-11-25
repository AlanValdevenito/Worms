#include "gusano.h"

Gusano::Gusano(uint8_t id, uint16_t x, uint16_t y, uint8_t vida, uint8_t color, uint8_t estado, uint8_t arma, uint8_t dir, uint8_t angulo) : Dto(GUSANO_CODE), id(id), x(x), y(y), vida(vida), color(color), estado(estado), arma(arma), direccion(dir), angulo(angulo) {}

Gusano::~Gusano() {}

bool Gusano::is_alive() { return true; }

uint16_t Gusano::x_pos() { return x; }

uint16_t Gusano::y_pos() { return y; }

uint8_t Gusano::get_id() { return id; }

uint8_t Gusano::get_vida() { return vida; }

uint8_t Gusano::get_color() { return color; }

uint8_t Gusano::get_estado() { return estado; }

uint8_t Gusano::get_arma() { return arma; }

uint8_t Gusano::get_direccion() { return direccion; }

uint8_t Gusano::get_angulo() { return angulo; }

Gusanos::Gusanos() : Dto(GUSANOS_CODE) {}

Gusanos::Gusanos(std::vector<std::shared_ptr<Gusano>> gs) : Dto(GUSANOS_CODE), gusanos(gs), id_turno(1), envio_proyectil(false) {}

Gusanos::~Gusanos() {} // VACIAR LA LISTAAA

bool Gusanos::is_alive() { return true; }

std::shared_ptr<Gusano> Gusanos::popGusano(int i)
{
    return this->gusanos[i];
}

std::vector<std::shared_ptr<Gusano>> Gusanos::return_gusanos_list() { return gusanos; }

void Gusanos::set_gusano_de_turno(uint8_t id) { id_turno = id; }

uint8_t Gusanos::get_gusano_de_turno() { return id_turno; }


void Gusanos::set_flag_proyectil(bool estado) { envio_proyectil = estado; }

bool Gusanos::get_flag_proyectil() { return envio_proyectil; }


uint8_t Gusanos::cantidad()
{
    return static_cast<uint8_t>(gusanos.size());
}
