#ifndef PARTIDA_VISTA_H
#define PARTIDA_VISTA_H

#include <iostream>
#include <exception>
#include <algorithm>
#include <map>
#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "client_camara.h"
#include "client_worm.h"
#include "client.h"
#include "viga.h"
#include "mover.h"
#include "dto.h"

const int SALTO_ADELANTE = 0;
const int SALTO_ATRAS = 1;

struct Temporizador {
    unsigned int cuentaRegresiva;

    unsigned int tiempoInicial;
    unsigned int tiempoActual;  
    unsigned int tiempoRestante; 
};

using namespace SDL2pp;

class Partida
{
private:
    SDLTTF ttf;

    Client &cliente;

    std::vector<std::shared_ptr<Viga>> vigas;
    std::map<int, Worm *> worms;
    int id_gusano_actual;

    std::map<int, SDL2pp::Texture *> texturas;
    std::map<int, SDL2pp::Color> colores;
    Font fuente;
    
    Temporizador temporizador;
    Camara camara;

    int x,y; // Enteros que almacenan la posicion del click en la ventana

public:
    Partida(Client &cliente);

    int iniciar();

    void inicializar_texturas(SDL2pp::Renderer &renderer);
    void inicializar_colores();

    void guardar_vigas();
    void guardar_worms(SDL2pp::Renderer &renderer, std::map<int, SDL2pp::Color> &colores);

    bool handleEvents(SDL2pp::Renderer &renderer);
    void enviarAtaque();

    bool actualizar(SDL2pp::Renderer &renderer, int it);

    void renderizar(SDL2pp::Renderer &renderer);
    void renderizar_temporizador(SDL2pp::Renderer &renderer);
    void renderizar_mapa(SDL2pp::Renderer &renderer);
    void renderizar_worms(SDL2pp::Renderer &renderer);

    float metros_a_pixeles(float metros);
    float centimetros_a_metros(float centimetros);
    float pixeles_a_metros(float pixeles);
    float metros_a_centimetros(float metros);

    void liberar_memoria();
};

#endif
