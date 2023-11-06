#include "worm.h"
#include <iostream>

Worm::Worm(b2World *b2world, float x, float y, uint8_t id) : x(x), y(y), id(id), hp(100), facingRight(true), is_alive(true), isRunning(false) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	body = b2world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xFD;

	fixtureDef.friction = 0.7f;
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
	facingRight = false;
	isRunning = true;
	body->SetLinearVelocity(b2Vec2(-2.0f, 0.0f));
}

void Worm::moveRight()
{	
	facingRight = true;
	isRunning = true;
    body->SetLinearVelocity(b2Vec2(2.0f, 0.0f));
}

void Worm::bat(std::list<Worm*>& worms) {
	float x = getXCoordinate();
	float distance;
	for (Worm *worm : worms) {
		distance = x - worm->getXCoordinate();
		if (distance == 0) continue;
		if (distance < 2.0f && distance > -2.0f) {
			if (facingRight) {
				worm->getBody()->ApplyLinearImpulseToCenter(b2Vec2(10.0f, 20.0f), true);
			} else {
				worm->getBody()->ApplyLinearImpulseToCenter(b2Vec2(-10.0f, 20.0f), true);
			}
			worm->takeDamage(10); // Sacarle la vida cuando se deje de mover
		}
	}
}

void Worm::makeDamage() {
	//std::cout << "make damage, damage taken = " << (int)damageTaken << "\n"; 
	if (hp <= damageTaken) {
		hp = 0;
		//is_alive = false;
	} else {
		hp -= damageTaken;
	}
	damageTaken = 0;
	
}

uint8_t Worm::getHp() {
	return hp;
}

bool Worm::isAlive() {
	return is_alive;
}

b2Body* Worm::getBody() {
	return body;
}

bool Worm::isMoving() {
	b2Vec2 wormVelocity = body->GetLinearVelocity();
	return wormVelocity.x != 0.0f || wormVelocity.y != 0.0f;
}

void Worm::takeDamage(uint8_t damage) {
	damageTaken += damage;
}

void Worm::setPlayerId(uint8_t id) {
	playerId = id;
}


Worm::~Worm() {}
