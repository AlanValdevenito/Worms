#ifndef MIRA_H
#define MIRA_H

#include <SDL2pp/SDL2pp.hh>

class Mira
{

private:
    // Atributo que almacena la textura de la animacion
    // Es una referencia para que esta pueda ser cambiada en cualquier momento segun el evento que este ocurriendo
    SDL2pp::Texture texture;
    // Entero que almacena el tamaño de cada frame (altura y acho).
    int size;
    // Angulo
    int angulo;

public:
    Mira(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, float x, float y, bool mirandoIzquierda);
    void aumentar_angulo();
    void decrementar_angulo();

    int get_angulo();
    void reiniciar();
};

#endif // MIRA_H