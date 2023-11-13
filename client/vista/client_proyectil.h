#ifndef _ANIMACION_PROYECTIL_H
#define _ANIMACION_PROYECTIL_H

#include <SDL2pp/SDL2pp.hh>

class AnimacionProyectil
{

private:
    SDL2pp::Texture texture; // Atributo que almacena la textura de la animacion

    int size; // Entero que almacena el tamaño de cada frame (altura y ancho).

    float x;
    float y;
    int angulo;
    int direccion;

    bool seLanzo;
    int exploto;
    int currentFrame;

    int tiempo;

public:
    AnimacionProyectil(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void update(float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion);
    void cambiar(std::string &ruta);

    void explotar(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void lanzarProyectil();
    bool seLanzoProyectil();

    void set_flag(int flag);
    int get_flag();

    float get_x();
    float get_y();

    void set_tiempo(int tiempoElegido);
    int get_tiempo();
};

#endif // _ANIMACION_PROYECTIL_H
