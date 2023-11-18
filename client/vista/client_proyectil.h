#ifndef _ANIMACION_PROYECTIL_H
#define _ANIMACION_PROYECTIL_H

#include <SDL2pp/SDL2pp.hh>

const int MOVIENDOSE_PROYECTIL = 0;
const int EXPLOTAR = 1;
const int EXPLOTO = 2;
const int APUNTANDO_PROYECTIL = 3;

class AnimacionProyectil
{

private:
    std::shared_ptr<SDL2pp::Texture> texture; // Atributo que almacena la textura de la animacion

    int size; // Entero que almacena el tamaño de cada frame (altura y ancho).

    float x;
    float y;
    int angulo;
    int direccion;

    int currentFrame;

    int tiempo;

    int estado;

public:
    AnimacionProyectil(SDL2pp::Renderer &renderer);

    void update(float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion, int nuevoEstado);
    void render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void renderizar_movimiento(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void renderizar_explosion(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void cambiar(std::shared_ptr<SDL2pp::Texture> texturaProyectil);

    void set_tiempo(int tiempoElegido);
    int get_tiempo();

    int get_estado();
};

#endif // _ANIMACION_PROYECTIL_H
