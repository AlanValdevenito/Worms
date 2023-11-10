#ifndef __ANIMACION_H__
#define __ANIMACION_H__

#include <SDL2pp/SDL2pp.hh>

class SdlTexture;
class Area;

// Esta clase se utiliza para gestionar una animacion a partir de una textura cargada.

class Animation {

private:
    SDL2pp::Texture texture; // Atributo que almacena la textura de la animacion

    int currentFrame; // Entero que almacena el indice del frame actual en la animacion
    int numFrames; // Entero que representa el numero todal de frames en la animacion
    int size; // Entero que almacena el tamaño de cada frame (altura y ancho)

public:
    Animation(SDL2pp::Renderer &renderer);

    void update(int it); // Actualiza la animacion. 
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest, SDL_RendererFlip &flipType); // Renderiza la animacion en el area especificada. El ultimo parametro se utiliza para controlar el volteo de la imagen.
};

#endif  //__ANIMATION_H__
