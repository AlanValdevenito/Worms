#ifndef __ANIMACION_H__
#define __ANIMACION_H__

#include <SDL2pp/SDL2pp.hh>

// Constante que se utiliza para determinar el tiempo entre frames.
// Funciona a una velocidad de 30 frames por segundo.
#define FRAME_RATE 1000000.0f/45.0f

class SdlTexture;
class Area;

// Esta clase se utiliza para gestionar una animacion a partir de una textura cargada.

class Animation {

private:
    // Avanza al siguiente frame de la animacion.
    void advanceFrame();
    // Atributo que almacena la textura de la animacion
    SDL2pp::Texture &texture;
    // Entero que almacena el indice del frame actual en la animacion.
    int currentFrame;
    // Entero que representa el numero todal de frames en la animacion.
    // Se calcula dividiendo la altura de la textura por su ancho.
    int numFrames;
    // Entero que almacena el tamaño de cada frame (altura y acho).
    int size;
    // Flotante que realiza un seguimiento del tiempo transcurrido desde el ultimo frame de animacion.
    float elapsed;

public:

    Animation(SDL2pp::Texture &texture);

    // Actualiza la animacion. 
    void update(float dt);
    // Renderiza la animacion en el area especificada. 
    // El ultimo parametro se utiliza para controlar el volteo de la imagen.
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest, SDL_RendererFlip &flipType);
};

#endif  //__ANIMATION_H__
