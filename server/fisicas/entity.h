#ifndef ENTITY_H
#define ENTITY_H

enum Direction {LEFT, RIGHT};

enum EntityType {WORM, BEAM, GREEN_GRENADE, BAZOOKA_ROCKET, BANANA, HOLY_GRENADE, DYNAMITE, AIR_STRIKE_ROCKET};

class Entity {
public:
    EntityType entityType;
    virtual void startContact() = 0;
    virtual void endContact() = 0;
    virtual ~Entity() {}
};
#endif