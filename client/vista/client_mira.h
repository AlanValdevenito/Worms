#ifndef MIRA_H
#define MIRA_H

#include <SDL2pp/SDL2pp.hh>

class AnimacionMira
{

private:
    SDL2pp::Texture texture; // Atributo que almacena la textura de la animacion
    int size; // Entero que almacena el tamaño de cada frame (altura y ancho).
    int angulo;

public:
    AnimacionMira(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, float x, float y, int direccion);

    void aumentar_angulo();
    void decrementar_angulo();
    int get_angulo();

    void reiniciar();
};

#endif // MIRA_H