#include "box2d/box2d.h"

class Worm
{
private:
    b2Body *body;
    float x;
    float y;
    uint8_t id;

public:
    bool isRunning;
    Worm(b2World *world, float x, float y, uint8_t id);
    float getXCoordinate();
    float getYCoordinate();
    uint8_t getId();
    void moveLeft();
    void moveRight();
    ~Worm();
};
