#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include "entity.h"


class HolyGrenade : public Entity {
public:
    EntityType entityType = HOLY_GRENADE;
    b2Body *body;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    HolyGrenade(b2World *world, float x, float y, int timeToExplotionInSeconds);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction, float angle, int power); 
    void explode();
    float getAngle();
    void startContact() override;
    void endContact() override;
    ~HolyGrenade();
};