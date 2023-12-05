#include "proyectil.h"

Proyectil::Proyectil(uint8_t code, bool exploto) : Dto(code), exploto(exploto) {}

Proyectil::Proyectil(uint8_t code, uint8_t id, bool exploto) : Dto(code, id), exploto(exploto) {}

Proyectil::~Proyectil() {}

bool Proyectil::is_alive() { return true; }

uint8_t Proyectil::get_tiempo() { return 0; }

uint8_t Proyectil::get_direccion() { return 0; }

uint8_t Proyectil::get_id() { return 0; }

bool Proyectil::get_exploto() { return exploto; }

void Proyectil::set_exploto(bool estado) { exploto = estado; }

Proyectiles::Proyectiles(std::vector<std::shared_ptr<Proyectil>> p) : Dto(PROYECTILES_CODE), proyectiles(p) {}

Proyectiles::~Proyectiles() {}

bool Proyectiles::is_alive() { return true; }

std::shared_ptr<Proyectil> Proyectiles::popProyectil(int i) { return this->proyectiles[i]; }

std::vector<std::shared_ptr<Proyectil>> Proyectiles::return_proyectiles() { return proyectiles; }

uint8_t Proyectiles::cantidad() { return static_cast<uint8_t>(proyectiles.size()); }
