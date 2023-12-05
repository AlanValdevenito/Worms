#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <iostream>
#include <exception>
#include <list>
#include "box2d/box2d.h"
#include "beam.h"
#include "worm.h"
#include "contact_listener.h"
#include <map>

class World
{
private:
    ContactListener contactListener;
    std::map<std::string, int> &config;
    std::list<Beam> beams;
    std::list<Worm *> worms;
    std::map<uint8_t, Worm *> wormsById;
    int idWorms = 0;

public:
    b2World world;
    // crea un mundo
    World(std::map<std::string, int> &config);

    // agrega una viga centrada en el punto (x, y) de ancho <width> y alto <height>
    void addBeam(float x, float y, float angle, BeamType type);

    // agrega un gusano en el punto (x, y)
    void addWorm(float x, float y);

    std::list<Beam> &getBeams();

    std::list<Worm *> &getWorms();

    std::map<uint8_t, Worm *> &getWormsById();

    b2Body *createStaticBody(float x, float y, float width, float height);

    b2Body *createDynamicBody(float x, float y);

    bool anyMovement();
    // avanza el mundo una fraccion de segundo
    void step(float timeStep);
    ~World();
};
#endif
