#ifndef ENTITY_H
#define ENTITY_H

enum Direction {LEFT, RIGHT};

enum EntityType {WORM, BEAM, GREEN_GRENADE, BAZOOKA_ROCKET, BANANA, HOLY_GRENADE, DYNAMITE, AIR_STRIKE_ROCKET, RED_GRENADE, FRAGMENT};

class Entity {
public:
    Entity(EntityType type) : entityType(type) {}
    EntityType entityType;
    virtual void startContact() = 0;
    virtual void endContact() = 0;
    virtual ~Entity() {}
};
#endif