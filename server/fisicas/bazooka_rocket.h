#ifndef BAZOOKA_ROCKET_H
#define BAZOOKA_ROCKET_H

#include "box2d/box2d.h"
#include "entity.h"
#include <iostream>
#include "utils.h"

class BazookaRocket : public Entity {
public:
    EntityType entityType = BAZOOKA_ROCKET;
    b2Body *body;
    Direction dir;
    int maxDamage;
    int explosionRadius;
    bool exploded = false;
    BazookaRocket(b2World *world, float x, float y, float angle);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void startContact() override;
    void explode();
    void endContact() override;
    void updateAngle();
    // devuelve el angulo en grados
    float getAngle();
    ~BazookaRocket();
};

#endif

