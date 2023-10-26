#ifndef BEAM_H
#define BEAM_H

#include "box2d/box2d.h"
#include <stdio.h>
#include <iostream>
#include <exception>


class Beam {
private:
    b2Body *body;

public:
    Beam(b2Body *body);
    ~Beam();
};
#endif