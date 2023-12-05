#ifndef SONIDO_H
#define SONIDO_H

#include <SDL2pp/SDL2pp.hh>
#include <memory>

class Sonido
{

private:
    std::unique_ptr<SDL2pp::Mixer> mixer;
    std::shared_ptr<SDL2pp::Chunk> sonido;

    bool reproducido;
    int loops;
    int canal;

public:
    Sonido(std::shared_ptr<SDL2pp::Chunk> sonido); 
    Sonido(); 

    void cambiar(std::shared_ptr<SDL2pp::Chunk> nuevoSonido, int loops = 0);
    void reproducir();
};

#endif // SONIDO_h
