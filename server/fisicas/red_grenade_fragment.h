#ifndef RED_GRENADE_FRAGMENT_H
#define RED_GRENADE_FRAGMENT_H

#include "box2d/box2d.h"
#include "entity.h"
#include <iostream>
#include <string>
#include <map>
#include "utils.h"

class RedGrenadeFragment : public Entity {
public:
    EntityType entityType = FRAGMENT;
    b2Body *body;
    Direction dir;
    int maxDamage;
    int explosionRadius;
    bool exploded = false;
    RedGrenadeFragment(b2World *world, float x, float y, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void startContact() override;
    void explode();
    void endContact() override;
    void destroy();
    // devuelve el angulo en grados
    float getAngle();
    ~RedGrenadeFragment();
};

#endif

