#ifndef BAZOOKA_ROCKET_H
#define BAZOOKA_ROCKET_H

#include "box2d/box2d.h"
#include "entity.h"
#include <iostream>
#include <string>
#include <map>
#include "utils.h"

class BazookaRocket : public Entity {
public:
    EntityType entityType = BAZOOKA_ROCKET;
    b2Body *body;
    Direction dir;
    int maxDamage;
    int explosionRadius;
    bool exploded = false;
    BazookaRocket(b2World *world, float x, float y, float angle, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void startContact() override;
    void explode();
    void destroy();
    void endContact() override;
    void updateAngle();
    // devuelve el angulo en grados
    float getAngle();
    ~BazookaRocket();
};

#endif

