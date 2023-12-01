#include "green_grenade.h"
#include "worm.h"
#include <iostream>



GreenGrenade::GreenGrenade(b2World *world, float x, float y,
                           int timeToExplotionInSeconds,
                           std::map<std::string, int>& config) : Entity(GREEN_GRENADE),maxDamage(config["greenGrenadeDamage"]), 
                                                                 explosionRadius(config["greenGrenadeRadius"]) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData.pointer = (uintptr_t)this;
	body = world->CreateBody(&bodyDef);

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

float GreenGrenade::getXCoordinate() {
    return body->GetPosition().x;
}

float GreenGrenade::getYCoordinate() {
    return body->GetPosition().y;
}

void GreenGrenade::shoot(Direction direction, float angle, int power) {
    
    float xComponent = (float(power) / 40.0f ) * cos(angle);
    float yComponent = (float(power) / 40.0f ) * sin(angle);
    if (direction == LEFT) {
        body->ApplyLinearImpulse(b2Vec2(-xComponent, yComponent), b2Vec2(0.025f, 0.025f), true);
    } else if (direction == RIGHT) {
        body->ApplyLinearImpulse(b2Vec2(xComponent, yComponent), b2Vec2(0.025f, 0.025f), true);
    } else {
        throw std::runtime_error("Invalid direction");
    }
}


void GreenGrenade::explode() {
    float xComponent; float yComponent;
    float damage;
    for ( b2Body* b = body->GetWorld()->GetBodyList(); b; b = b->GetNext())
    {   
        float distance = getDistance(body->GetPosition().x, body->GetPosition().y,
                                     b->GetPosition().x, b->GetPosition().y);
        if (b->GetType() == b2_dynamicBody && distance <= explosionRadius && distance != 0.0f) {
            Entity *entity = (Entity*)b->GetUserData().pointer;
	  
            if (entity != NULL) {
                if ((entity->entityType == WORM)) {;
                    Worm *worm = (Worm*)entity;
                    damage = maxDamage * (1 - distance / explosionRadius);
                    worm->takeDamage(damage);
                    xComponent = 5*(b->GetPosition().x - body->GetPosition().x) / distance;
                    yComponent = abs(b->GetPosition().y - body->GetPosition().y) + 5.0f;
                    worm->applyImpulse(xComponent, yComponent);
                }
            } 
            
        }
    }
    exploded = true;
}

int GreenGrenade::getTimeLeftToExplode() {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    int timePassed = std::chrono::duration_cast<std::chrono::seconds> (now - spawnTime).count();
    return timeToExplotion - timePassed;
}

float GreenGrenade::getAngle() {
    return body->GetAngle() * 180.0f / 3.14f;
}

void GreenGrenade::update() {
    if (not exploded) {
        std::chrono::steady_clock::time_point now;
        now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds> (now - spawnTime).count() >= timeToExplotion) {
            explode();
        }
    }
}

void GreenGrenade::destroy() {
    body->GetWorld()->DestroyBody(body);
}

void GreenGrenade::startContact() {}


void GreenGrenade::endContact() {}


GreenGrenade::~GreenGrenade() {}