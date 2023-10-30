#ifndef VISTA_H
#define VISTA_H 

// Probando .gitignore

#include <iostream>
#include <exception>
#include <algorithm>

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
    // std::vector<Worm *> worms;
    // Worm worm_turno;

public:
    Vista(Client &cliente);

    int iniciar();
    void guardar_vigas();

    bool handleEvents(Worm &worm);

    void renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, Worm &worm, unsigned int tiempoRestante);
    void renderizar_temporizador(SDL2pp::Renderer &renderer, SDL2pp::Font &font, unsigned int tiempoRestante);
    void renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua);
    // void renderizar_nombre(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion);
    // void renderizar_vida(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion);

    void actualizar(Worm &worm, int it);

    float metros_a_pixeles(float metros);
    float centimetros_a_metros(float centimetros);
};

#endif
