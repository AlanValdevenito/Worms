#include "beam.h"


Beam::Beam(b2Body *body, float x, float y, float width, float height) :
    body(body),
    x(x),
    y(y),
    width(width),
    height(height) {}

float Beam::getXCoordinate() {
    return x;
}

float Beam::getYCoordinate() {
    return y;
}

float Beam::getWidth() {
    return width;
}

float Beam::getHeight() {
    return height;
}


Beam::~Beam() {}