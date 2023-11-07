#ifndef ENTITY_H
#define ENTITY_H


enum EntityType {WORM, BEAM};

class Entity {
public:
    EntityType entityType;
    virtual void startContact() = 0;
    virtual void endContact() = 0;
    virtual ~Entity() {}
};
#endif