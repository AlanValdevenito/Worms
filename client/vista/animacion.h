#ifndef __ANIMACION_H__
#define __ANIMACION_H__

#include <SDL2pp/SDL2pp.hh>
#include <memory>

class SdlTexture;
class Area;

// Esta clase se utiliza para gestionar una animacion a partir de una textura cargada.

class Animacion {

private:
    std::shared_ptr<SDL2pp::Texture> textura;

    int currentFrame; // Entero que almacena el indice del frame actual en la animacion
    int numFrames; // Entero que representa el numero todal de frames en la animacion
    int size; // Entero que almacena el tamaño de cada frame (altura y ancho)

    bool repetirAnimacion;

public:
    Animacion(std::shared_ptr<SDL2pp::Texture> textura, bool repetirAnimacion = true);

    void update(int it = 0); // Actualiza la animacion. 
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest, SDL_RendererFlip &flipType, int angulo = 0); // Renderiza la animacion en el area especificada. El ultimo parametro se utiliza para controlar el volteo de la imagen.

    void cambiar(std::shared_ptr<SDL2pp::Texture> nuevaTextura);

    void no_repetir_animacion();
    bool completa();

    void set_current_frame(int nuevoCurrentFrame);
};

#endif  //__ANIMATION_H__
