#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <iostream>
#include <exception>
#include <list>
#include "box2d/box2d.h"
#include "beam.h"


class World {
private:
    b2World world;
    std::list<Beam> beams;
public:
    
    // crea un mundo
    World();

    // agrega una viga centrada en el punto (x, y) de ancho <width> y alto <height>
    void addBeam(float x, float y, float width, float height);
    
    std::list<Beam> getBeams();

    b2Body* createStaticBody(float x, float y, float width, float height);

    // avanza el mundo una fraccion de segundo
    void step();

    ~World();
};
#endif