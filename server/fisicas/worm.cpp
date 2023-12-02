#include "worm.h"
#include <iostream>

Worm::Worm(b2World *b2world, float x, float y, uint8_t id,
		   std::map<std::string, int>& config) : Entity(WORM),
												hp(config["wormHp"]), 
												id(id), 
												teamNumber(0),
												numberOfContacts(0),
												speed(config["wormSpeed"]),
												facingRight(false), 
												is_alive(true), 
												damageTaken(0),
												isRunning(false),
												state(MOVING),
												playerId(-1),
												highestYCoordinateReached(0),
												jumpTimeout(0),
												actualWeapon(NO_WEAPON),
												direction(LEFT),
												angle(0),
												firstTimeFalling(true),
												infiniteHp(false)
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

	ammunition[BATE_WEAPON] = 1;
	ammunition[GREEN_GRENADE_WEAPON] = config["greenGrenadeAmmunition"];
	ammunition[BAZOOKA_WEAPON] = config["bazookaAmmunition"];
	ammunition[BANANA_WEAPON] = config["bananaAmmunition"];
	ammunition[RED_GRENADE_WEAPON] = config["redGrenadeAmmunition"];
	ammunition[MORTERO_WEAPON] = config["morteroAmmunition"];
	ammunition[AIR_STRIKE_WEAPON] = config["airStrikeAmmunition"];
	ammunition[TELEPORT_WEAPON] = config["teleportAmmunition"];
	ammunition[HOLY_GRENADE_WEAPON] = config["holyGrenadeAmmunition"];
	ammunition[DYNAMITE_WEAPON] = config["dynamiteAmmunition"];
	ammunition[NO_WEAPON] = 99999999;
	ammunition[USED_WEAPON] = 99999999;

	// cuerpo rectangular
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
	b2RayCastInput input;
	input.p1 = body->GetPosition();
	input.p2 = b2Vec2(body->GetPosition().x - 1, body->GetPosition().y - 1);
	input.maxFraction = 0.75;
	b2Vec2 normal(0, 0);
	int minFraction = 10;
	
	b2Vec2 intersectionNormal(0,0);
	for (b2Body* b = body->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetType() == b2_staticBody) {
			b2Fixture* f = b->GetFixtureList();
				
			b2RayCastOutput output;
			if (f->RayCast( &output, input, 1)) {
				if (output.fraction <= minFraction) {
					minFraction = output.fraction;
					normal = output.normal;
				}
			}		
		}
	}
	float theta = 3.14f / 2.0f;
	b2Vec2 velocity = b2Vec2(std::min(0.0f, speed * (cos(theta) * normal.x - sin(theta) * normal.y)),
							 std::max(0.0f, speed * (sin(theta) * normal.x + cos(theta) * normal.y)));

	if (actualWeapon == NO_WEAPON || actualWeapon == USED_WEAPON) {
		isRunning = true;
		if (velocity == b2Vec2(0.0f,0.0f)) velocity = b2Vec2(-speed, 0.0f);
		body->SetLinearVelocity(velocity);
		state = MOVING;
	}
	facingRight = false;
	direction = LEFT;
}

void Worm::moveRight()
{	
	if (numberOfContacts == 0) return;
	b2RayCastInput input;
	input.p1 = body->GetPosition();
	input.p2 = b2Vec2(body->GetPosition().x + 1, body->GetPosition().y - 1);
	input.maxFraction = 0.75f;
	b2Vec2 normal(0, 0);
	int minFraction = 10;
	b2Vec2 intersectionNormal(0,0);
	for (b2Body* b = body->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetType() == b2_staticBody) {
			b2Fixture* f = b->GetFixtureList();
				
			b2RayCastOutput output;
			if (f->RayCast( &output, input, 1)) {
				if (output.fraction <= minFraction) {
					minFraction = output.fraction;
					normal = output.normal;
				}
			}		
		}
	}
	float theta = -3.14f / 2.0f;
	b2Vec2 velocity = b2Vec2(std::max(0.0f, speed * (cos(theta) * normal.x - sin(theta) * normal.y)),
							 std::max(0.0f, speed * (sin(theta) * normal.x + cos(theta) * normal.y)));
	

	// si no tiene arma, que se mueva
	// si tiene arma, cambia la direccion a la derecha pero no se mueve
	if (actualWeapon == NO_WEAPON || actualWeapon == USED_WEAPON) {
		isRunning = true;
		if (velocity == b2Vec2(0.0f, 0.0f) || velocity.x == 0) {
			velocity = b2Vec2(speed, 0.0f);
		}
		body->SetLinearVelocity(velocity);
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
	if (numberOfContacts == 0 || jumpTimeout > 0) return;
	float xComponent; float yComponent;
	if (facingRight) {
		xComponent = -2.0f;
	} else {
		xComponent = 2.0f;
	}
	yComponent = 5.0f;
	body->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
	state = JUMPING_BACKWARD;
	jumpTimeout = 42;
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
			worm->takeDamage(10);
			worm->state = FLYING;
		}
	}
}

void Worm::makeDamage() {
	if (hp <= damageTaken) {
		hp = 0;
		state = DEAD;
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
	if (infiniteHp) return;
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
	if (fallDistance > 2.0f && not firstTimeFalling) {
		takeDamage(std::min((int)fallDistance, 25));
	}
	highestYCoordinateReached = 0;
	if (firstTimeFalling) {firstTimeFalling = false;}
}

void Worm::equipWeapon(uint8_t weapon) {
	if (ammunition[weapon] == 0) return;
	if (weapon == 11) {
		actualWeapon = 11;
		state = STATIC;
	} else if (weapon == actualWeapon || weapon == NO_WEAPON) {
		actualWeapon = NO_WEAPON;
		state = STATIC;
	} else {
		actualWeapon = weapon;
		state = EQUIPING_WEAPON;
	}
}

void Worm::increaseHp(int extraHp) {
	hp += extraHp;
}

void Worm::applyImpulse(float x, float y) {
	body->ApplyLinearImpulseToCenter(b2Vec2(x, y), true);
	state = FLYING;
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


b2Vec2 Worm::getVelocity() {
	return body->GetLinearVelocity();
}
Worm::~Worm() {}
