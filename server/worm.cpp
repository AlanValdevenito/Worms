#include "worm.h"
#include <iostream>

Worm::Worm(b2World *b2world, float x, float y, uint8_t id) : x(x), y(y), id(id), hp(100), isRunning(false) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	body = b2world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 0.1f);

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

void Worm::bat(std::list<Worm*>& worms) {
	float x = getXCoordinate();
	float distance;
	for (Worm *worm : worms) {
		distance = x - worm->getXCoordinate();
		if (distance == 0) continue;
		if (distance < 2.0f || distance > -2.0f) {
			worm->getBody()->ApplyLinearImpulseToCenter(b2Vec2(10.0f, 10.0f), true);
			worm->makeDamage(10);
			std::cout << "vida del gusano golpeado : " << (int)worm->getHp() << "\n";
		}
	}
}

void Worm::makeDamage(uint8_t damage) {
	this->hp = this->hp - damage;
}

uint8_t Worm::getHp() {
	return hp;
}

b2Body* Worm::getBody() {
	return body;
}


Worm::~Worm() {}
