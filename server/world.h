#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <iostream>
#include <exception>
#include <list>
#include "box2d/box2d.h"
#include "beam.h"
#include "worm.h"

class World
{
private:
    b2World world;
    std::list<Beam> beams;
    std::list<Worm> worms;

public:
    // crea un mundo
    World();

    // agrega una viga centrada en el punto (x, y) de ancho <width> y alto <height>
    void addBeam(float x, float y, float angle, BeamType type);

    // agrega un gusano en el punto (x, y)
    void addWorm(float x, float y);

    std::list<Beam> &getBeams();

    std::list<Worm> &getWorms();

    b2Body *createStaticBody(float x, float y, float width, float height);

    b2Body *createDynamicBody(float x, float y);

    // avanza el mundo una fraccion de segundo
    void step();

    ~World();
};
#endif
