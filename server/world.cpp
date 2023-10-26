#include "world.h"



World::World() : world(b2Vec2(0, -10)) {}

b2Body* World::createStaticBody(float x, float y, float width, float height) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x, y);
	b2Body *body = world.CreateBody(&bodyDef);
	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(width / 2, height / 2);
	body->CreateFixture(&bodyShape, 0.0f);
    return body;
}

void World::addBeam(float x, float y, float width, float height) {
    // creo el cuerpo de la viga
    b2Body *beamBody = createStaticBody(x, y, width, height);
    // creo la viga pasandole el cuerpo
    Beam beam(beamBody, x, y, width, height);
    // agrego la viga a la lista de vigas
    beams.push_back(beam);
}

std::list<Beam> World::getBeams() {
    return beams;
}

void World::step() {
    world.Step(1/60, 10, 10);
}

World::~World() {}
