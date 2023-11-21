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
    uint8_t damageTaken = 0;
    bool isRunning;
    int state = MOVING;
    uint8_t playerId = -1;
    EntityType entityType = WORM;
    float highestYCoordinateReached;
    int jumpTimeout = 0;
    
    Worm(b2World *b2world, float x, float y, uint8_t id, std::map<std::string, int>& config);
    float getXCoordinate();
    float getYCoordinate();
    uint8_t getId();
    uint8_t getState();
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
    uint8_t getTeamNumber();
    void jump();
    void jumpBackward();
    void startContact() override;
    void endContact() override;
    ~Worm() override;
};
#endif
