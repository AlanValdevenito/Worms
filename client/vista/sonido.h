#ifndef SONIDO_H
#define SONIDO_H

#include <SDL2pp/SDL2pp.hh>
#include <memory>

class Sonido
{

private:
    std::unique_ptr<SDL2pp::Mixer> mixer;
    std::unique_ptr<SDL2pp::Chunk> sonido;

public:
    bool reproducido;
    Sonido(std::string ruta);

    void cambiar(std::unique_ptr<SDL2pp::Chunk> nuevoSonido);

    void reproducir();
    void detener();
};

#endif // SONIDO_h
