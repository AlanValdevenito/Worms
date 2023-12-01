#include "mortero_rocket.h"
#include "worm.h"


MorteroRocket::MorteroRocket(b2World *world, float x, float y, float angle,
                             std::map<std::string, int>& config) : Entity(BAZOOKA_ROCKET),maxDamage(config["morteroDamage"]),
                                                                   explosionRadius(config["morteroRadius"]) {
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

    body->SetTransform(b2Vec2(x, y), angle);
}


float MorteroRocket::getXCoordinate() {
    return body->GetPosition().x;
}

float MorteroRocket::getYCoordinate() {
    return body->GetPosition().y;
}


void MorteroRocket::shoot(Direction direction, float angle, int power) {
    
    float xComponent = (float(power) / 10.0f ) * cos(angle);
    float yComponent = (float(power) / 10.0f ) * sin(angle);
    if (direction == LEFT) {
        body->ApplyLinearImpulseToCenter(b2Vec2(-xComponent, yComponent), true);
    } else if (direction == RIGHT) {
        body->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
    } else {
        throw std::runtime_error("Invalid direction");
    }
    dir = direction;
}



void MorteroRocket::startContact() {
    if (exploded) return;
    explode();
}
    
void MorteroRocket::endContact() {}

void MorteroRocket::explode() {
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


float MorteroRocket::getAngle() {
    return body->GetAngle() * 180.0f / 3.14f;
}


void MorteroRocket::updateAngle() {
    float angle = atan2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
    body->SetTransform(body->GetPosition(), angle);
}

void MorteroRocket::destroy() {
    body->GetWorld()->DestroyBody(body);
}

MorteroRocket::~MorteroRocket() {}