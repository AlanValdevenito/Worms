#include "world.h"

World::World() : world(b2Vec2(0, -10)) {
    world.SetContactListener(&contactListener);
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

std::list<Worm*> &World::getWorms()
{
    return worms;
}

void World::addWorm(float x, float y)
{   
    idWorms = idWorms + 1;
    Worm *worm = new Worm(&world, x, y, idWorms);
    worms.push_back(worm);
    wormsById[idWorms] = worm;

}

void World::step(float timeStep)
{
    world.Step(timeStep, 10, 10);
    //std::cout << "coordenada x = " << worms.front().getXCoordinate() << "\ncoordenada y = " << worms.front().getYCoordinate() << "\n";
}

std::map<uint8_t, Worm*>& World::getWormsById() {
    return wormsById;
}

/*bool World::isInsideABeam(float x, float y) {

}*/ 
World::~World() {
    for (Worm *worm : worms) {
        delete worm;
    }
    //delete world;
}
