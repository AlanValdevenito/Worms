#include "world.h"

World::World(std::map<std::string, int> &config) : config(config), world(b2Vec2(0, -10))
{
    world.SetContactListener(&contactListener);
    createStaticBody(-500, 400, 10, 1000); // pared izquierda
    createStaticBody(500, 400, 10, 1000);  // pared derecha
    createStaticBody(0, 900, 1000, 10);    // techo
    createStaticBody(0, -5, 1000, 9.5f);   // piso

    createStaticBody(0, -1, 6500, 0.5f);
}

b2Body *World::createStaticBody(float x, float y, float width, float height)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    b2Body *body = world.CreateBody(&bodyDef);
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 0.7f;
    body->CreateFixture(&fixtureDef);

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
    Beam beam(&world, x, y, angle, type);
    // agrego la viga a la lista de vigas
    beams.push_back(beam);
}

std::list<Beam> &World::getBeams()
{
    return beams;
}

std::list<Worm *> &World::getWorms()
{
    return worms;
}

void World::addWorm(float x, float y)
{
    idWorms = idWorms + 1;
    Worm *worm = new Worm(&world, x, y, idWorms, config);
    worms.push_back(worm);
    wormsById[idWorms] = worm;
}

void World::step(float timeStep)
{
    world.Step(timeStep, 10, 10);
}

std::map<uint8_t, Worm *> &World::getWormsById()
{
    return wormsById;
}

bool World::anyMovement()
{
    for (b2Body *b = world.GetBodyList(); b; b = b->GetNext())
    {
        b2Vec2 velocity = b->GetLinearVelocity();
        if (velocity.x != 0.0f || velocity.y != 0.0f)
        {
            return true;
        }
    }
    return false;
}

World::~World()
{
    for (Worm *worm : worms)
    {
        delete worm;
    }
}
