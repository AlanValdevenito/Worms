#ifndef RED_GRENADE_H
#define RED_GRENADE_H

#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include <string>
#include <map>
#include "entity.h"
#include "utils.h"



class RedGrenade : public Entity {
public:
    EntityType entityType = RED_GRENADE;
    b2Body *body;
    int maxDamage;
    int explosionRadius;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    bool exploded = false;
    RedGrenade(b2World *world, float x, float y, int timeToExplotionInSeconds, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void explode();
    void update();
    float getAngle();
    void startContact() override;
    void endContact() override;
    ~RedGrenade();
};
#endif