#include "cliente_id.h"

ClienteId::ClienteId(uint8_t id) : Dto(CLIENTE_ID_CODE, id), id(id) {}

ClienteId::~ClienteId() {}

bool ClienteId::is_alive() { return true; }
