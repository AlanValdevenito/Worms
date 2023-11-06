#ifndef ARMA_H
#define ARMA_H

#include <SDL2pp/SDL2pp.hh>

class Arma
{

private:
     SDL2pp::Texture &texture;
    // Entero que almacena el indice del frame actual en la animacion.
    int currentFrame;
    bool animacionCompleta;

public:
    Arma(SDL2pp::Texture &texture);

    // Actualiza la animacion. 
    void update();
    void reiniciar();
    bool get_animacion_completa();

    // Renderiza la arma.
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType);
};

#endif // ARMA_H