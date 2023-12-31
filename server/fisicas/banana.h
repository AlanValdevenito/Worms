#ifndef BANANA_H
#define BANANA_H

#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include "entity.h"
#include "utils.h"
#include <string>
#include <map>


class Banana : public Entity {
public:
    EntityType entityType = BANANA_GRENADE;
    b2Body *body;
    int maxDamage;
    int explosionRadius;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    bool exploded = false;
    Banana(b2World *world, float x, float y, int timeToExplotionInSeconds, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void explode();
    void update();
    void destroy();
    float getAngle();
    int getTimeLeftToExplode();
    void startContact() override;
    void endContact() override;
    ~Banana();
};
#endif