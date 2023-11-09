#ifndef ARMA_H
#define ARMA_H

#include <SDL2pp/SDL2pp.hh>

class Arma
{

private:
    // Atributo que almacena la textura de la animacion
    // Es una referencia para que esta pueda ser cambiada en cualquier momento segun el evento que este ocurriendo
    SDL2pp::Texture texture;
    // Entero que almacena el indice del frame actual en la animacion.
    int currentFrame;
    // Entero que representa el numero todal de frames en la animacion.
    // Se calcula dividiendo la altura de la textura por su ancho.
    int numFrames;
    // Entero que almacena el tamaño de cada frame (altura y acho).
    int size;
    // Booleano que indica si la animacion se completo
    bool animacionCompleta;

public:
    Arma(SDL2pp::Renderer &renderer);

    // Actualiza la animacion. 
    void update();
    void reiniciar();
    bool get_animacion_completa();

    // Renderiza la arma.
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType);
};

#endif // ARMA_H