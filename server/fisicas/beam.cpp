#include "beam.h"

Beam::Beam(b2World *world, float x, float y, float angle, BeamType type)
    : Entity(BEAM), x(x), y(y), angle(angle), type(type) {
    if (type == SHORT) {
      width = SHORT_BEAM_WIDTH;
    } else if (type == LONG) {
      width = LONG_BEAM_WIDTH;
    } else {
      throw std::runtime_error("Invalid BeamType");
    }
    height = BEAM_HEIGHT;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    bodyDef.userData.pointer = (uintptr_t)this;
    body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(width / 2, height / 2);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 0.7f;
    body->CreateFixture(&fixtureDef);
    body->SetTransform(b2Vec2(x, y), angle * 3.14 / 180);
      
    

    // seteo el angulo de la viga pasandolo a radianes
    
}

float Beam::getXCoordinate() { return x; }

float Beam::getYCoordinate() { return y; }

float Beam::getWidth() { return width; }

float Beam::getHeight() { return height; }

float Beam::getAngle() { return angle; }

void Beam::startContact() {}

void Beam::endContact() {}

Beam::~Beam() {}
