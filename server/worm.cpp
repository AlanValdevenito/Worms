#include "worm.h"

Worm::Worm(b2Body *body, float x, float y, uint8_t id) : body(body), x(x), y(y), id(id) {}

float Worm::getXCoordinate()
{
    return x;
}

float Worm::getYCoordinate()
{
    return y;
}

uint8_t Worm::getId()
{
    return id;
}

Worm::~Worm() {}