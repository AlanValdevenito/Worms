#ifndef POTENCIA_H
#define POTENCIA_H

#include <SDL2pp/SDL2pp.hh>

class Potencia
{

private:
    SDL2pp::Texture texture; // Atributo que almacena la textura de la animacion

    int currentFrame;
    int numFrames;
    int size; // Entero que almacena el tamaño de cada frame (altura y ancho)

public:
    Potencia(SDL2pp::Renderer &renderer);

    void update(); // Actualiza la animacion. 
    void render(SDL2pp::Renderer &renderer, float x, float y, int direccion, int angulo); // Renderiza la potencia.

    int get_current_frame();

    void reiniciar();
};

#endif // POTENCIA_H