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

public:
    std::list<Beam> beams;
    // crea un mundo con gravedad <gravity>
    World(b2Vec2 gravity);

    // agrega una viga centrada en el punto (x, y) de ancho <width> y alto <height>
    void addBeam(float x, float y, float width, float height);
    
    b2Body* createStaticBody(float x, float y, float width, float height);

    ~World();
};
#endif