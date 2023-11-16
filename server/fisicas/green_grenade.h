#ifndef GREEN_GRENADE_H
#define GREEN_GRENADE_H

#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include "entity.h"
#include "utils.h"



class GreenGrenade : public Entity {
public:
    EntityType entityType = GREEN_GRENADE;
    b2Body *body;
    int maxDamage;
    int explosionRadius;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    GreenGrenade(b2World *world, float x, float y, int timeToExplotionInSeconds);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void explode();
    float getAngle();
    void startContact() override;
    void endContact() override;
    ~GreenGrenade();
};
#endif