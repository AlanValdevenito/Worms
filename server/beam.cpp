#include "beam.h"

Beam::Beam(b2Body *body, float x, float y, float angle, BeamType type)
    : body(body), x(x), y(y), angle(angle), type(type) {
  if (type == SHORT) {
    width = SHORT_BEAM_WIDTH;
  } else if (type == LONG) {
    width = LONG_BEAM_WIDTH;
  } else {
    throw std::runtime_error("Invalid BeamType");
  }
  height = BEAM_HEIGHT;

  // seteo el angulo de la viga pasandolo a radianes
  body->SetTransform(b2Vec2(x, y), angle * 3.14 / 180);
}

float Beam::getXCoordinate() { return x; }

float Beam::getYCoordinate() { return y; }

float Beam::getWidth() { return width; }

float Beam::getHeight() { return height; }

float Beam::getAngle() { return angle; }

Beam::~Beam() {}
