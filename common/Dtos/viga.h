#ifndef VIGA_H
#define VIGA_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

#include "dto.h"
#include "constantes.h"

class Viga : public Dto
{
private:
    uint16_t x;
    uint16_t y;
    uint16_t ancho;
    uint16_t alto;

public:
    Viga(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto);
    ~Viga();
    bool is_alive() override;
    uint16_t x_pos() override;
    uint16_t y_pos() override;
    uint16_t return_ancho() override;
    uint16_t return_alto() override;
};

class Vigas : public Dto
{
private:
    // std::list<std::shared_ptr<Viga>> vigas;
    std::vector<std::shared_ptr<Viga>> vigas;

public:
    Vigas();
    Vigas(std::vector<std::shared_ptr<Viga>> vs);
    ~Vigas();
    bool is_alive() override;
    std::shared_ptr<Viga> popViga(int i);
    uint8_t cantidad() override;
    std::vector<std::shared_ptr<Viga>> return_vigas_list();
};
#endif
