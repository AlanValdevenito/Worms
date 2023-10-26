#ifndef BEAM_H
#define BEAM_H

#include "box2d/box2d.h"
#include <stdio.h>
#include <iostream>
#include <exception>


class Beam {
private:
    b2Body *body;
    float x;
    float y;
    float width;
    float height;

public:
    Beam(b2Body *body, float x, float y, float width, float height);
    float getXCoordinate();
    float getYCoordinate();
    float getWidth();
    float getHeight();
    ~Beam();
};
#endif