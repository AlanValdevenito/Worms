#include "worm.h"
#include <iostream>

Worm::Worm(b2World *b2world, float x, float y, uint8_t id,
		   std::map<std::string, int>& config) : Entity(WORM),
												hp(config["wormHp"]), 
												id(id), 
												numberOfContacts(0),
												speed(config["wormSpeed"]),
												facingRight(false), 
												is_alive(true), 
												isRunning(false),
												direction(LEFT)
												{
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData.pointer = (uintptr_t)this;
	body = b2world->CreateBody(&bodyDef);
	
	// cuerpo circular
	b2FixtureDef fixtureDef;
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0); 
    circleShape.m_radius = 0.5f; 
    fixtureDef.shape = &circleShape; 
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.7f;
    fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xFD;
    body->CreateFixture(&fixtureDef); 

	// sensor de cuerpo circular 
	b2FixtureDef sensorFixtureDef;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.4f, 0.25f, b2Vec2(0.0f,-0.25f), 0);
	sensorFixtureDef.isSensor = true;
	sensorFixtureDef.shape = &polygonShape;
	sensorFixtureDef.filter.categoryBits = 0x02;
    sensorFixtureDef.filter.maskBits = 0xFD;
	body->CreateFixture(&sensorFixtureDef);

	body->SetFixedRotation(true);


	// cuerpo rectangular

	/*
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
	*/
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
	if (numberOfContacts == 0) return;
	if (actualWeapon == NO_WEAPON) {
		isRunning = true;
		body->SetLinearVelocity(b2Vec2(-speed, 0.0f));
		state = MOVING;
	}
	facingRight = false;
	direction = LEFT;
}

void Worm::moveRight()
{	
	if (numberOfContacts == 0) return;
	// si no tiene arma, que se mueva
	// si tiene arma, cambia la direccion a la derecha pero no se mueve
	if (actualWeapon == NO_WEAPON) {
		isRunning = true;
		body->SetLinearVelocity(b2Vec2(speed, 0.0f));
		state = MOVING;
	}
	facingRight = true;
	direction = RIGHT;
}

void Worm::jump() {
	if (numberOfContacts == 0 || jumpTimeout > 0) return;
	float xComponent; float yComponent;
	if (facingRight) {
		xComponent = 2.0f;
	} else {
		xComponent = -2.0f;
	}
	yComponent = 5.0f;
	body->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
	state = JUMPING_FORWARD;
	jumpTimeout = 42;
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
			worm->state = FLYING;
		}
	}
}

void Worm::makeDamage() {
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
	std::cout << "Worm:: takeDamage()\n";
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

void Worm::updateAngle() {
    angle = atan2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

float Worm::getAngle() {
	return angle * 180.0f / 3.14f;
}

void Worm::startContact() {
	numberOfContacts++;
	angle = 0;
	state = MOVING;
	float fallDistance = highestYCoordinateReached - body->GetPosition().y;
	if (fallDistance > 2.0f) {
		takeDamage(std::min((int)fallDistance, 25));
	}
	highestYCoordinateReached = body->GetPosition().y;
}

void Worm::equipWeapon(uint8_t weapon) {
	
	if (weapon == actualWeapon || weapon == NO_WEAPON) {
		actualWeapon = NO_WEAPON;
		state = MOVING;
	} else {
		actualWeapon = weapon;
		state = EQUIPING_WEAPON;
		//state = AIMING;
	}
}

void Worm::applyImpulse(float x, float y) {
	std::cout << "worm apply Impulse, playerId = " << playerId << "\n";
	body->ApplyLinearImpulseToCenter(b2Vec2(x, y), true);
}

uint8_t Worm::getWeapon() {
	return actualWeapon;
}

uint8_t Worm::getDirection() {
	return direction;
}

void Worm::endContact() {
	numberOfContacts--;
}

Worm::~Worm() {}
