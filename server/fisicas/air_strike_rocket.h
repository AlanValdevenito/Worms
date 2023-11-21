#ifndef AIR_STRIKE_ROCKET_H
#define AIR_STRIKE_ROCKET_H

#include "box2d/box2d.h"
#include "entity.h"
#include <iostream>
#include "utils.h"
#include <string>
#include <map>

class AirStrikeRocket : public Entity {
public:
    EntityType entityType = AIR_STRIKE_ROCKET;
    b2Body *body;
    Direction dir;
    int maxDamage;
    int explosionRadius;
    bool exploded = false;
    AirStrikeRocket(b2World *world, float x, float y, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(); 
    void startContact() override;
    void explode();
    void endContact() override;
    // devuelve el angulo en grados
    ~AirStrikeRocket();
};

#endif

