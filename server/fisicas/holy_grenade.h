#ifndef HOLY_GRENADE_H
#define HOLY_GRENADE_H

#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include "entity.h"
#include "utils.h"
#include <map>
#include <string>

class HolyGrenade : public Entity {
public:
    EntityType entityType = HOLY_GRENADE;
    b2Body *body;
    int maxDamage;
    int explosionRadius;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    bool exploded = false;
    HolyGrenade(b2World *world, float x, float y, int timeToExplotionInSeconds, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void explode();
    void update();
    void destroy();
    int getTimeLeftToExplode();
    float getAngle();
    void startContact() override;
    void endContact() override;
    ~HolyGrenade();
};
#endif
