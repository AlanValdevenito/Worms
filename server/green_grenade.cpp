#include "green_grenade.h"

GreenGrenade::GreenGrenade(b2World *world, float x, float y, int timeToExplotionInSeconds) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData.pointer = (uintptr_t)this;
	body = world->CreateBody(&bodyDef);
	
    
    /*b2FixtureDef fixtureDef;
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0); //position, relative to body position
    circleShape.m_radius = 0.005f; //radius
    fixtureDef.shape = &circleShape; //this is a pointer to the shape above
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef); //add a fixture to the body*/

    

    b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.05f, 0.05f);
    b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xFD;

	
	body->CreateFixture(&fixtureDef);
    timeToExplotion = timeToExplotionInSeconds;
    spawnTime = std::chrono::steady_clock::now();
}

float GreenGrenade::getXCoordinate() {
    return body->GetPosition().x;
}

float GreenGrenade::getYCoordinate() {
    return body->GetPosition().y;
}

void GreenGrenade::shoot(int angle, int power) {
    body->ApplyLinearImpulseToCenter(b2Vec2(1.5 * cos(angle), 1.5 * sin(angle)), true);
}

void GreenGrenade::startContact() {}
    
void GreenGrenade::endContact() {}


GreenGrenade::~GreenGrenade() {}