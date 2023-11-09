#include "green_grenade.h"

GreenGrenade::GreenGrenade(b2World *world, float x, float y, int timeToExplotionInSeconds) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData.pointer = (uintptr_t)this;
	body = world->CreateBody(&bodyDef);
	b2FixtureDef fixtureDef;
    b2CircleShape circleShape;
    circleShape.m_p.Set(x, y); //position, relative to body position
    circleShape.m_radius = 0.1f; //radius
    fixtureDef.shape = &circleShape; //this is a pointer to the shape above
    fixtureDef.restitution = 0.1f;
    body->CreateFixture(&fixtureDef); //add a fixture to the body

    timeToExplotion = timeToExplotionInSeconds;
}

float GreenGrenade::getXCoordinate() {
    return body->GetPosition().x;
}

float GreenGrenade::getYCoordinate() {
    return body->GetPosition().y;
}

void GreenGrenade::shoot(int angle, int power) {
    body->ApplyLinearImpulseToCenter(b2Vec2(power * cos(angle), power * sin(angle)), true);
}

void GreenGrenade::startContact() {}
    
void GreenGrenade::endContact() {}


GreenGrenade::~GreenGrenade() {}