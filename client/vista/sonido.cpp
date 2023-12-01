#include "sonido.h"

Sonido::Sonido(std::string ruta): mixer(std::make_unique<SDL2pp::Mixer>(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096)),
                                      sonido(std::make_unique<SDL2pp::Chunk>(DATA_PATH + ruta)),
                                      reproducido(false) {}

void Sonido::cambiar(std::unique_ptr<SDL2pp::Chunk> nuevoSonido) {
}

void Sonido::reproducir() {
    if (not reproducido) {
        this->sonido->SetVolume(SDL_MIX_MAXVOLUME / 10);
        this->mixer->PlayChannel(-1, *(this->sonido), 0, 0);

        this->reproducido = true;
    }
}

void Sonido::detener() {
    // this->mixer->PauseChannel(-1);
}