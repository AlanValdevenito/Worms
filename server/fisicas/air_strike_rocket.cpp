#include "air_strike_rocket.h"
#include "worm.h"


AirStrikeRocket::AirStrikeRocket(b2World *world, float x, float y,
                                std::map<std::string, int>& config) : Entity(AIR_STRIKE_ROCKET),
                                                                      maxDamage(config["airStrikeDamage"]),
                                                                      explosionRadius(config["airStrikeRadius"]) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData.pointer = (uintptr_t)this;
	body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.15f, 0.025f);
    b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.5f;
    fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xFD;
    body->CreateFixture(&fixtureDef);
    
    // sensor
    b2FixtureDef sensorFixtureDef;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.151f, 0.026f);

	sensorFixtureDef.isSensor = true;
	sensorFixtureDef.shape = &polygonShape;
    sensorFixtureDef.filter.categoryBits = 0x02;
    sensorFixtureDef.filter.maskBits = 0xFD;

	body->CreateFixture(&sensorFixtureDef);
}


float AirStrikeRocket::getXCoordinate() {
    return body->GetPosition().x;
}

float AirStrikeRocket::getYCoordinate() {
    return body->GetPosition().y;
}


void AirStrikeRocket::shoot() {
    body->ApplyLinearImpulseToCenter(b2Vec2(0, -0.50f), true);
}



void AirStrikeRocket::startContact() {
    if (exploded) return;
    explode();
}
    
void AirStrikeRocket::endContact() {}

void AirStrikeRocket::explode() {
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

void AirStrikeRocket::destroy() {
    body->GetWorld()->DestroyBody(body);
}

AirStrikeRocket::~AirStrikeRocket() {}