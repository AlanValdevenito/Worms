#ifndef DTO_H
#define DTO_H

#include <iostream>
#include <string>
#include <vector>

const char VACIO[] = "";

class Dto
{
private:
    uint8_t code;
    uint8_t id_cliente;

public:
    Dto();
    explicit Dto(uint8_t code);
    explicit Dto(uint8_t code, uint8_t id);
    virtual ~Dto();

    virtual std::string return_line();
    virtual uint8_t orientation();
    virtual bool is_alive();
    virtual uint16_t x_pos();
    virtual uint16_t y_pos();
    virtual uint16_t return_alto();
    virtual uint16_t return_ancho();
    virtual void *popViga();
    virtual uint8_t cantidad();
    uint8_t get_cliente_id();
    uint8_t return_code();
};
#endif
