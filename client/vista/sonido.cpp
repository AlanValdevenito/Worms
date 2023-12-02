#include "sonido.h"

Sonido::Sonido(std::string ruta): mixer(std::make_unique<SDL2pp::Mixer>(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096)),
                                      sonido(std::make_unique<SDL2pp::Chunk>(DATA_PATH + ruta)),
                                      reproducido(false),
                                      loops(0) {}

void Sonido::cambiar(std::unique_ptr<SDL2pp::Chunk> nuevoSonido, int loops) {
    this->sonido = std::move(nuevoSonido);
    this->reproducido = false;
    this->loops = loops;
}

void Sonido::reproducir() {
    if (not reproducido) {
        this->sonido->SetVolume(SDL_MIX_MAXVOLUME / 10);
        this->canal = this->mixer->PlayChannel(-1, *(this->sonido), 0, this->loops);

        this->reproducido = true;
    }
}
