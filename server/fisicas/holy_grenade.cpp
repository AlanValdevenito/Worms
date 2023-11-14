#include "holy_grenade.h"
#include "worm.h"
#include <iostream>



HolyGrenade::HolyGrenade(b2World *world, float x, float y, int timeToExplotionInSeconds) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData.pointer = (uintptr_t)this;
	body = world->CreateBody(&bodyDef);
	
    
    /*b2FixtureDef fixtureDef;
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0); //position, relative to body position
    circleShape.m_radius = 0.025f; //radius
    fixtureDef.shape = &circleShape; //this is a pointer to the shape above
    fixtureDef.restitution = 0.2f;
    fixtureDef.density = 1.5f;
    fixtureDef.friction = 0.5f;
    fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xFD;
    body->CreateFixture(&fixtureDef); //add a fixture to the body*/

    

    b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.025f, 0.025f);
    b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.5f;
    fixtureDef.restitution = 0.2f;
	fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xFD;

	
	body->CreateFixture(&fixtureDef);
    timeToExplotion = timeToExplotionInSeconds;
    spawnTime = std::chrono::steady_clock::now();
 }

float HolyGrenade::getXCoordinate() {
    return body->GetPosition().x;
}

float HolyGrenade::getYCoordinate() {
    return body->GetPosition().y;
}

void HolyGrenade::shoot(Direction direction, float angle, int power) {
    
    float xComponent = (float(power) / 40.0f ) * cos(angle);
    float yComponent = (float(power) / 40.0f ) * sin(angle);
    std::cout << "xComponent = " << xComponent << " yComponent = " << yComponent << "\n";
    if (direction == LEFT) {
        body->ApplyLinearImpulse(b2Vec2(-xComponent, yComponent), b2Vec2(0.025f, 0.025f), true);
    } else if (direction == RIGHT) {
        body->ApplyLinearImpulse(b2Vec2(xComponent, yComponent), b2Vec2(0.025f, 0.025f), true);
    } else {
        throw std::runtime_error("Invalid direction");
    }
}

float getDistan(float x1, float y1, float x2, float y2) {
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}

void HolyGrenade::explode() {
    float xComponent; float yComponent;
    for ( b2Body* b = body->GetWorld()->GetBodyList(); b; b = b->GetNext())
    {   
        float distance = getDistan(body->GetPosition().x, body->GetPosition().y,
                                     b->GetPosition().x, b->GetPosition().y);
        if (b->GetType() == b2_dynamicBody && distance < 4.0f && distance != 0.0f) {
            Entity *entity = (Entity*)b->GetUserData().pointer;
	  
            if (entity != NULL) {
                if ((entity->entityType == WORM)) {;
                    Worm *worm = (Worm*)entity;
                    worm->takeDamage(30);
                }
            } 
            xComponent = 5*(b->GetPosition().x - body->GetPosition().x) / distance;
            yComponent = abs(b->GetPosition().y - body->GetPosition().y) + 5.0f;
            b->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
        }
    }
}


float HolyGrenade::getAngle() {
    return body->GetAngle() * 180.0f / 3.14f;
}

void HolyGrenade::startContact() {}
    
void HolyGrenade::endContact() {}


HolyGrenade::~HolyGrenade() {}