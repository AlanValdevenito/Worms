#ifndef CLIENTE_ID_H
#define CLIENTE_ID_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"
#include "constantes.h"

class ClienteId : public Dto
{
private:
    uint8_t id;
public:
    ClienteId(uint8_t id);
    ~ClienteId();
    bool is_alive() override;
    // uint8_t get_cliente_id();
};
#endif