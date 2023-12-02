#ifndef ANIMACION_DINAMITA_H
#define ANIMACION_DINAMITA_H

#include <SDL2pp/SDL2pp.hh>

#include "vista_arma.h"
#include "client_apuntado.h"

class AnimacionDinamita: public Arma
{

private:
    Animation movimiento;
    Explosion explosion;

    Sonido sonido;

    int tiempo;

public:
    AnimacionDinamita(SDL2pp::Renderer &renderer, std::map<int, std::shared_ptr<SDL2pp::Texture>> &texturas, std::map<int, std::shared_ptr<SDL2pp::Chunk>> &sonidos);

    void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) override;
    
    void render(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion) override;
    void renderizar_tiempo(SDL2pp::Renderer &renderer, SDL2pp::Color color, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void set_tiempo(int tiempoElegido) override;
    int get_tiempo() override;
};

#endif // ANIMACION_DINAMITA_H
