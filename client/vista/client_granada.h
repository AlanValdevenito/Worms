#ifndef _GRANADA_H
#define _GRANADA_H

#include <SDL2pp/SDL2pp.hh>

class Granada
{

private:
    SDL2pp::Texture texture; // Atributo que almacena la textura de la animacion

    int size; // Entero que almacena el tamaño de cada frame (altura y ancho).

    float x;
    float y;

    bool seLanzo;
    int exploto;
    int currentFrame;

public:
    Granada(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, float camara);
    void update(float nuevoX, float nuevoY);

    void explotar(SDL2pp::Renderer &renderer, float camara);

    void lanzarGranada();
    bool seLanzoGranada();

    void set_flag(int flag);
    int get_flag();

    float get_x();
    float get_y();
};

#endif // _GRANADA_H
