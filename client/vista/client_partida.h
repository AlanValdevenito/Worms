#ifndef PARTIDA_VISTA_H
#define PARTIDA_VISTA_H

#include <iostream>
#include <exception>
#include <algorithm>
#include <map>
#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "client_worm.h"
#include "client.h"
#include "viga.h"
#include "mover.h"
#include "dto.h"

using namespace SDL2pp;

class Partida
{
private:
    Client &cliente;
    std::vector<std::shared_ptr<Viga>> vigas;
    std::map<int, Worm *> worms;

public:
    Partida(Client &cliente);

    int iniciar();
    void guardar_vigas();
    void guardar_worms(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, SDL2pp::Texture &potencia);

    bool handleEvents(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites);

    void renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, unsigned int tiempoRestante);
    void renderizar_temporizador(SDL2pp::Renderer &renderer, SDL2pp::Font &font, unsigned int tiempoRestante);
    void renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua);
    void renderizar_worms(SDL2pp::Renderer &renderer);
    // void renderizar_nombre(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion);

    bool actualizar(SDL2pp::Renderer &renderer, int it);

    float metros_a_pixeles(float metros);
    float centimetros_a_metros(float centimetros);

    void liberar_memoria();
};

#endif
