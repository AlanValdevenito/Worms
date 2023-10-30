#ifndef VISTA_H
#define VISTA_H 

#include <iostream>
#include <exception>
#include <algorithm>
#include <map>

#include <SDL2pp/SDL2pp.hh>

#include "client_worm.h"
#include "client.h"
#include "viga.h"
#include "mover.h"
#include "dto.h"

using namespace SDL2pp;

class Vista
{
private:
    Client &cliente;
    std::vector<Viga *> vigas;
    std::map<int, Worm *> worms;

public:
    Vista(Client &cliente);

    int iniciar();
    void guardar_vigas();
    void guardar_worms(SDL2pp::Texture &sprites);

    bool handleEvents();

    void renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, unsigned int tiempoRestante);
    void renderizar_temporizador(SDL2pp::Renderer &renderer, SDL2pp::Font &font, unsigned int tiempoRestante);
    void renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua);
    void renderizar_worms(SDL2pp::Renderer &renderer);
    // void renderizar_nombre(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion);
    // void renderizar_vida(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion);

    void actualizar(int it);

    float metros_a_pixeles(float metros);
    float centimetros_a_metros(float centimetros);

    void liberar_memoria();
};

#endif
