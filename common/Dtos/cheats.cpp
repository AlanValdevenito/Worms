#include "cheats.h"


Cheat::Cheat(uint8_t id, uint8_t code) : Dto(CHEAT_CODE, id), cheat(code) {}

Cheat::~Cheat() {}

bool Cheat::is_alive() { return true; }

uint8_t Cheat::get_cheat() { return cheat; }
