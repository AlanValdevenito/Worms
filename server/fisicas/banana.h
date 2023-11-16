#ifndef BANANA_H
#define BANANA_H

#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include "entity.h"
#include "utils.h"


class Banana : public Entity {
public:
    EntityType entityType = BANANA;
    b2Body *body;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    Banana(b2World *world, float x, float y, int timeToExplotionInSeconds);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void explode();
    float getAngle();
    void startContact() override;
    void endContact() override;
    ~Banana();
};
#endif