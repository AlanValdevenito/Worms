#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include <chrono>
#include "entity.h"


class Dynamite : public Entity {
public:
    EntityType entityType = DYNAMITE;
    b2Body *body;
    std::chrono::steady_clock::time_point spawnTime;
    int timeToExplotion;
    Dynamite(b2World *world, float x, float y, int timeToExplotionInSeconds);
    float getXCoordinate();
    float getYCoordinate();
    void shoot(Direction direction); 
    void explode();
    float getAngle();
    void startContact() override;
    void endContact() override;
    ~Dynamite();
};