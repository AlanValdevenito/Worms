#include "worm.h"
#include <iostream>

Worm::Worm(b2World *b2world, float x, float y, uint8_t id,
		   std::map<std::string, int>& config) : Entity(),
												hp(config["wormHp"]), 
												id(id), 
												//configuraciones(YAML::LoadFile("/configuracion.yml")),
												numberOfContacts(0),
												speed(config["wormSpeed"]),
												
												
												facingRight(false), 
												is_alive(true), 
												isRunning(false)
												//speed(config["wormSpeed"])
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
	//std::cout << "worm -> moveLeft\n";
	if (numberOfContacts == 0) return;
	facingRight = false;
	isRunning = true;
	body->SetLinearVelocity(b2Vec2(-speed, 0.0f));
	state = MOVING;
}

void Worm::moveRight()
{	
	//std::cout << "worm -> moveRight\n";
	if (numberOfContacts == 0) return;
	facingRight = true;
	isRunning = true;
    body->SetLinearVelocity(b2Vec2(speed, 0.0f));
	state = MOVING;
}

void Worm::jump() {
	if (numberOfContacts == 0 || jumpTimeout > 0) return;
	std::cout << "Worm::jump(), number of contacts > 0\n";
	float xComponent; float yComponent;
	if (facingRight) {
		xComponent = 2.0f;
	} else {
		xComponent = -2.0f;
	}
	yComponent = 5.0f;
	body->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
	state = JUMPING_FORWARD;
	jumpTimeout = 5;
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
	//std::cout << "Worm::makeDamage\n";
	if (hp <= damageTaken) {
		hp = 0;
		state = DEAD;
		//is_alive = false;
	} else {
		hp -= damageTaken;
	}
	damageTaken = 0;
	//std::cout << "Worm::makeDamage, hp = " << (int)hp << "\n";
	
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
	float fallDistance = highestYCoordinateReached - body->GetPosition().y;
	if (fallDistance > 2.0f) {
		takeDamage(std::min((int)fallDistance, 25));
	}
	std::cout << "fallDistance = " << fallDistance << "\n";
	highestYCoordinateReached = body->GetPosition().y;
}

void Worm::endContact() {
	numberOfContacts--;
}

Worm::~Worm() {}
