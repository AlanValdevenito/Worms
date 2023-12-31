#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include "entity.h"
#include <map>
#include <string>
#include "utils.h"

class Dynamite : public Entity {
public:
    EntityType entityType = DYNAMITE;
    b2Body *body;
    int maxDamage;
    int explosionRadius;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    bool exploded = false;
    Dynamite(b2World *world, float x, float y, int timeToExplotionInSeconds, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction); 
    void explode();
    void update();
    float getAngle();
    int getTimeLeftToExplode();
    void destroy();
    void startContact() override;
    void endContact() override;
    ~Dynamite();
};
#endif