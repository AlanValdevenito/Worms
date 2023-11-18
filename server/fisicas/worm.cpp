#include "worm.h"
#include <iostream>

Worm::Worm(b2World *b2world, float x, float y, uint8_t id) : x(x), 
															 y(y), 
															 id(id), 
															 //configuraciones(YAML::LoadFile("/configuracion.yml")),
															 hp(100), 
															 facingRight(false), 
															 is_alive(true), 
															 isRunning(false) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData.pointer = (uintptr_t)this;
	body = b2world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xFD;

	fixtureDef.friction = 0.7f;
	body->CreateFixture(&fixtureDef);

	// le agrego un sensor 
	b2FixtureDef sensorFixtureDef;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.05f, 0.05f, b2Vec2(0.0f,-0.5f), 0);
	sensorFixtureDef.isSensor = true;
	sensorFixtureDef.shape = &polygonShape;
	sensorFixtureDef.filter.categoryBits = 0x02;
    sensorFixtureDef.filter.maskBits = 0xFD;
	body->CreateFixture(&sensorFixtureDef);
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
	//std::cout << "worm -> moveLeft\n";
	if (numberOfContacts == 0) return;
	facingRight = false;
	isRunning = true;
	body->SetLinearVelocity(b2Vec2(-2.0f, 0.0f));
	state = MOVING;
}

void Worm::moveRight()
{	
	//std::cout << "worm -> moveRight\n";
	if (numberOfContacts == 0) return;
	facingRight = true;
	isRunning = true;
    body->SetLinearVelocity(b2Vec2(2.0f, 0.0f));
	state = MOVING;
}

void Worm::jump() {
	if (numberOfContacts == 0) return;
	float xComponent; float yComponent;
	if (facingRight) {
		xComponent = 2.0f;
	} else {
		xComponent = -2.0f;
	}
	yComponent = 5.0f;
	body->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
	state = JUMPING_FORWARD;
}

void Worm::jumpBackward() {
	if (numberOfContacts == 0) return;
	float xComponent; float yComponent;
	if (facingRight) {
		xComponent = -2.0f;
	} else {
		xComponent = 2.0f;
	}
	yComponent = 7.0f;
	body->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
	state = JUMPING_BACKWARD;
}


void Worm::bat(std::list<Worm*>& worms, int angle) {
	float x = getXCoordinate();
	float distance;
	float xComponent; float yComponent;
	for (Worm *worm : worms) {
		distance = x - worm->getXCoordinate();
		if (distance == 0) continue;
		if (distance < 2.0f && distance > -2.0f) {
			float angleInRadians = angle * 3.14f / 180.0f;
			if (facingRight) {
				xComponent = 20.0f * cos(angleInRadians);
			} else {
				xComponent = -20.0f * cos(angleInRadians);
			}
			yComponent = 40.0f*sin(angleInRadians);
			worm->getBody()->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
			worm->takeDamage(10); // Sacarle la vida cuando se deje de mover
		}
	}
}

void Worm::makeDamage() {
	//std::cout << "make damage, damage taken = " << (int)damageTaken << "\n"; 
	if (hp <= damageTaken) {
		hp = 0;
		state = DEAD;
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

uint8_t Worm::getState() {
	return (uint8_t)state;
}

void Worm::setTeamNumber(uint8_t number) {
	teamNumber = number;
}

uint8_t Worm::getTeamNumber() {
	return teamNumber;
}

void Worm::startContact() {
	numberOfContacts++;
	state = MOVING;
}

void Worm::endContact() {
	numberOfContacts--;
}

Worm::~Worm() {}
