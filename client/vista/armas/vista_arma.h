#ifndef ARMA_H
#define ARMA_H

#include <SDL2pp/SDL2pp.hh>

#include "client_explosion.h"

const int ARMA_EQUIPANDO = 6;
const int ARMA_ESPERANDO = 7;
const int ARMA_APUNTANDO = 3;
const int ARMA_USANDO = 4;
const int ARMA_MOVIENDOSE = 0;
const int ARMA_EXPLOTAR = 1;
const int ARMA_EXPLOTO = 2;
const int ARMA_DESEQUIPAR = 5;

class Arma
{

private:

public:
    float x;
    float y;
    int estado;

    Arma(int estadoInicial);

    // Metodos virtuales puros (palabra clave 'virtual' y sufijo '= 0')
    // Se declaran en la clase base pero no se definen, dejando su implementacion a las clases derivadas
    // Las clases derivadas estan obligadas a implementar estos metodos
    virtual void update(float nuevoX, float nuevoY, int nuevoEstado, int nuevoAngulo = 0, int nuevaDireccion = 0, int nuevoTiempo = 0, int id = 0) = 0;
    virtual void render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior, int direccion = 0) = 0;

    // Metodos virtuales (palabra clave 'virtual')
    // Se declaran en la clase base y se implementan tambien en la base
    // Estos metodos son heredados por las clases derivadas
    // Las clases derivadas pueden implementar estos metodos y cuando llamen al metodo llamaran a su implementacion
    virtual void set_tiempo(int tiempoElegido);
    virtual int get_tiempo();

    virtual void aumentar_angulo();
    virtual void decrementar_angulo();
    virtual int get_angulo();

    virtual void aumentar_potencia();
    virtual int get_potencia();

    virtual int get_estado();

    virtual ~Arma();
};

#endif // ARMA_H
