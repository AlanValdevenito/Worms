#include "partidas_lista.h"

ListaDePartidas::ListaDePartidas() : Dto(LISTA_DE_PARTIDAS_CODE) {}

ListaDePartidas::ListaDePartidas(uint8_t id, uint8_t s) : Dto(LISTA_DE_PARTIDAS_CODE, id), seleccionada(s) {}

ListaDePartidas::~ListaDePartidas() {}

bool ListaDePartidas::is_alive() { return true; }

void ListaDePartidas::addOption(uint8_t o)
{
    partidas.push_back(o);
}

std::list<uint8_t> ListaDePartidas::return_list()
{
    return partidas;
}

