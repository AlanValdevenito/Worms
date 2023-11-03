#include "worm.h"

Worm::Worm(b2World *world, float x, float y, uint8_t id) : x(x), y(y), id(id), isRunning(false) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;

	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
}

float Worm::getXCoordinate()
{
    return body->GetPosition().x;
}

float Worm::getYCoordinate()
{
    return body->GetPosition().y;
}

uint8_t Worm::getId()
{
    return id;
}

void Worm::moveLeft() {
	isRunning = true;
	body->SetLinearVelocity(b2Vec2(-0.6f, 0.0f));
}

void Worm::moveRight()
{	
	isRunning = true;
    body->SetLinearVelocity(b2Vec2(0.6f, 0.0f));
}



Worm::~Worm() {}
