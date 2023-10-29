#ifndef PARTIDAS_LISTA_H
#define PARTIDAS_LISTA_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <string>

#include "dto.h"
#include "constantes.h"

class ListaDePartidas : public Dto
{
private:
    std::list<uint8_t> partidas;
    std::string mensaje;

public:
    uint8_t seleccionada;

    ListaDePartidas();
    ListaDePartidas(uint8_t s);
    ~ListaDePartidas();
    bool is_alive() override;
    std::list<uint8_t> return_list();
    void addOption(uint8_t o);
    // uint8_t get_id();
};

#endif