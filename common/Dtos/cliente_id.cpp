#include "cliente_id.h"

ClienteId::ClienteId(uint8_t id) : Dto(CLIENTE_ID_CODE, id), id(id) {}

ClienteId::~ClienteId() {}

bool ClienteId::is_alive() { return true; }

// uint8_t ClienteId::get_cliente_id() { return id; }