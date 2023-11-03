#ifndef POTENCIA_H
#define POTENCIA_H

#include <SDL2pp/SDL2pp.hh>

class Potencia
{

private:
    // Atributo que almacena la textura de la animacion
    // Es una referencia para que esta pueda ser cambiada en cualquier momento segun el evento que este ocurriendo
    SDL2pp::Texture &texture;
    // Entero que almacena el indice del frame actual en la animacion.
    int currentFrame;
    // Entero que representa el numero todal de frames en la animacion.
    // Se calcula dividiendo la altura de la textura por su ancho.
    int numFrames;
    // Entero que almacena el tamaño de cada frame (altura y acho).
    int size;
    int angulo;

public:
    Potencia(SDL2pp::Texture &potencia);

    // Renderiza la potencia.
    void render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda);
    // Actualiza la animacion. 
    void update();
    void reiniciar();
    float calcular_angulo(float adyacente);
    int get_current_frame();
};

#endif // POTENCIA_H