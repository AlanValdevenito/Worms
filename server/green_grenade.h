#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include "entity.h"



class GreenGrenade : public Entity {
public:
    EntityType entityType = GREEN_GRENADE;
    b2Body *body;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    GreenGrenade(b2World *world, float x, float y, int timeToExplotionInSeconds);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(int angle, int power); 
    void startContact() override;
    void endContact() override;
    ~GreenGrenade();
};