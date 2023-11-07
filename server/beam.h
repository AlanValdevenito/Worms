#ifndef BEAM_H
#define BEAM_H

#include "box2d/box2d.h"
#include <exception>
#include <iostream>
#include <stdio.h>
#include "entity.h"

#define SHORT_BEAM_WIDTH 3
#define LONG_BEAM_WIDTH 6
#define BEAM_HEIGHT 0.8

enum BeamType { SHORT, LONG };

class Beam : public Entity {
private:
  
  b2Body *body;
  float x;
  float y;
  float width;
  float height;
  float angle;
  BeamType type;
  

public:
  EntityType entityType = BEAM;
  // construye una viga centrada en el punto (x, y) rotada un ángulo <angle> (en
  // grados) de tipo type.
  Beam(b2World *world, float x, float y, float angle, BeamType type);
  float getXCoordinate();
  float getYCoordinate();
  float getWidth();
  float getHeight();
  float getAngle();
  void startContact() override;
  void endContact() override;
  ~Beam();
};
#endif
