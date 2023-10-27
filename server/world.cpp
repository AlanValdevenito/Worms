#include "world.h"

World::World() : world(b2Vec2(0, -10)) {}

b2Body *World::createStaticBody(float x, float y, float width, float height)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    b2Body *body = world.CreateBody(&bodyDef);
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(width / 2, height / 2);
    body->CreateFixture(&bodyShape, 0.0f);
    return body;
}

b2Body *World::createDynamicBody(float x, float y)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    b2Body *body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.2f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    return body;
}

void World::addBeam(float x, float y, float angle, BeamType type)
{

    float width;
    float height = 0.8;
    if (type == SHORT)
    {
        width = 3;
    }
    else if (type == LONG)
    {
        width = 6;
    }
    else
    {
        throw std::runtime_error("Invalid BeamType");
    }
    // creo el cuerpo de la viga
    b2Body *beamBody = createStaticBody(x, y, width, height);
    // creo la viga pasandole el cuerpo
    Beam beam(beamBody, x, y, angle, type);
    // agrego la viga a la lista de vigas
    beams.push_back(beam);
}

std::list<Beam> &World::getBeams()
{
    return beams;
}

std::list<Worm> &World::getWorms()
{
    return worms;
}

void World::addWorm(float x, float y)
{
    b2Body *body = createDynamicBody(x, y);
    Worm worm(body, x, y, 0);
    worms.push_back(worm);
}

void World::step()
{
    world.Step(1 / 60, 10, 10);
}

World::~World() {}
