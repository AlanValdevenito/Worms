#include "box2d/box2d.h"
#include "entity.h"
#include <iostream>

class BazookaRocket : public Entity {
public:
    EntityType entityType = BAZOOKA_ROCKET;
    b2Body *body;
    bool exploded = false;
    BazookaRocket(b2World *world, float x, float y);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void startContact() override;
    void explode();
    void endContact() override;
    ~BazookaRocket();
};

