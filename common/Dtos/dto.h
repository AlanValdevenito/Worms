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

public:
    Dto();
    explicit Dto(uint8_t code);
    virtual ~Dto();

    virtual std::string return_line();
    virtual uint8_t orientation();
    virtual bool is_alive();
    virtual uint16_t x_pos();
    virtual uint16_t y_pos();
    virtual uint16_t return_alto();
    virtual uint16_t return_ancho();
    uint8_t return_code();
};
#endif
