#include "world.h"



World::World(b2Vec2 gravity) : world(gravity) {}

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
    Beam beam(beamBody);
    // agrego la viga a la lista de vigas
    beams.push_back(beam);
}

World::~World() {}
