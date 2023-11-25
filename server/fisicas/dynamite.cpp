#include "dynamite.h"
#include "worm.h"

#include <iostream>



Dynamite::Dynamite(b2World *world, float x, float y,
                    int timeToExplotionInSeconds,
                    std::map<std::string, int>& config) : Entity(DYNAMITE),maxDamage(config["dynamiteDamage"]),
                                                          explosionRadius(config["dynamiteRadius"]) {
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

float Dynamite::getXCoordinate() {
    return body->GetPosition().x;
}

float Dynamite::getYCoordinate() {
    return body->GetPosition().y;
}

void Dynamite::shoot(Direction direction) {
    float x = getXCoordinate();
    float y = getYCoordinate();
    if (direction == LEFT) {
        body->SetTransform(b2Vec2(x - 0.5f, y + 0.5f), 0);
    } else {
        body->SetTransform(b2Vec2(x + 0.5f, y + 0.5f), 0);
    }
    
}



void Dynamite::explode() {
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

int Dynamite::getTimeLeftToExplode() {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    int timePassed = std::chrono::duration_cast<std::chrono::seconds> (now - spawnTime).count();
    return timeToExplotion - timePassed;
}


void Dynamite::update() {
    if (not exploded) {
        std::chrono::steady_clock::time_point now;
        now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds> (now - spawnTime).count() >= timeToExplotion) {
            explode();
        }
    }
}

float Dynamite::getAngle() {
    return body->GetAngle() * 180.0f / 3.14f;
}

void Dynamite::destroy() {
    body->GetWorld()->DestroyBody(body);
}


void Dynamite::startContact() {}
    
void Dynamite::endContact() {}


Dynamite::~Dynamite() {}