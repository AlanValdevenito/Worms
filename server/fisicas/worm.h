#ifndef WORM_H 
#define WORM_H

#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include "entity.h"
#include <map>
#include <string>
#include "yaml-cpp/yaml.h"

const int MOVING = 0;
const int JUMPING_FORWARD = 1;
const int JUMPING_BACKWARD = 2;
const int EQUIPING_WEAPON = 3;
const int AIMING = 4;
const int DEAD = 5;
const int FLYING = 7;
const int STATIC = 8;
const int FALLING = 9;

const int BATE_WEAPON = 7;
const int GREEN_GRENADE_WEAPON = 2;
const int BAZOOKA_WEAPON = 0;
const int BANANA_WEAPON = 4;
const int HOLY_GRENADE_WEAPON = 5;
const int DYNAMITE_WEAPON = 6;
const int TELEPORT_WEAPON = 9;
const int AIR_STRIKE_WEAPON = 8;
const int RED_GRENADE_WEAPON = 3;
const int MORTERO_WEAPON = 1;
const int NO_WEAPON = 10;
const int USED_WEAPON = 11;


class Worm : public Entity {
private:
    b2Body *body;
    
    uint8_t hp;
    uint8_t id;
    uint8_t teamNumber;

public:
    int numberOfContacts;
    int speed;
    bool facingRight;
    bool is_alive;
    uint8_t damageTaken;
    bool isRunning;
    int state;
    uint8_t playerId;
    EntityType entityType = WORM;
    float highestYCoordinateReached;
    int jumpTimeout;
    int actualWeapon;
    uint8_t direction;
    float angle;
    bool firstTimeFalling;
    std::map<int, int> ammunition;
    Worm(b2World *b2world, float x, float y, uint8_t id, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    uint8_t getId();
    uint8_t getState();
    b2Vec2 getVelocity(); 
    void moveLeft();
    void moveRight();
    b2Body* getBody();
    void bat(std::list<Worm*>& worms, int angle);
    void makeDamage();
    uint8_t getHp();
    bool isAlive(); // Delete
    bool isMoving();
    void takeDamage(uint8_t damage);
    void setPlayerId(uint8_t id);
    void setTeamNumber(uint8_t number);
    void equipWeapon(uint8_t weapon);
    void applyImpulse(float x, float y);
    void increaseHp(int extraHp);
    uint8_t getWeapon();
    uint8_t getTeamNumber();
    uint8_t getDirection();
    float getAngle();
    void updateAngle();
    void jump();
    void jumpBackward();
    void startContact() override;
    void endContact() override;
    ~Worm() override;
};
#endif
