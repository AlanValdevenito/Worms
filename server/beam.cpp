#include "beam.h"


Beam::Beam(b2Body *body, float x, float y, float angle, BeamType type) :
    body(body),
    x(x),
    y(y),
    type(type) {
        if (type == SHORT) {
            width = 3;
        } else if (type == LONG) {
            width = 6;
        } else {
            throw std::runtime_error("Invalid BeamType");
        }
        height = 0.8;
        
        // seteo el angulo de la viga
        body->SetTransform(b2Vec2(x, y), angle);
    }

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

float Beam::getAngle() {
    return angle;
}

Beam::~Beam() {}

