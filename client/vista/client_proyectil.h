#ifndef _ANIMACION_PROYECTIL_H
#define _ANIMACION_PROYECTIL_H

#include <SDL2pp/SDL2pp.hh>

class AnimacionProyectil
{

private:
    std::shared_ptr<SDL2pp::Texture> texture; // Atributo que almacena la textura de la animacion

    int size; // Entero que almacena el tamaño de cada frame (altura y ancho).

    float x;
    float y;
    int angulo;
    int direccion;

    int flag; // Entero que indica: 
              // (0/false): Cuando el servidor no envia posiciones ya que no se lanzo un proyectil
              // (1/true): Cuando el servidor envia posiciones ya que se lanzo un proyectil

    int currentFrame;

    int tiempo;

    bool debeExplotar;
    bool enMovimiento;

public:
    AnimacionProyectil(SDL2pp::Renderer &renderer);

    void update(float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion);
    void render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void renderizar_movimiento(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void renderizar_explosion(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void cambiar(std::shared_ptr<SDL2pp::Texture> texturaProyectil);

    void set_flag(int flag);
    int get_flag();

    void set_tiempo(int tiempoElegido);
    int get_tiempo();
};

#endif // _ANIMACION_PROYECTIL_H
