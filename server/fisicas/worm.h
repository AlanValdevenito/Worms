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
const int NO_WEAPON = 10;
const int FLYING = 7;



/*const int BATE = 7;
const int GRANADA_VERDE = 2;
const int BAZOOKA = 0;
const int BANANA = 4;
const int GRANADA_SANTA = 5;
const int DINAMITA = 6;
const int TELETRANSPORTACION = 9;
const int ATAQUE_AEREO = 8;
const int GRANADA_ROJA = 3;
const int MORTERO = 1;
*/

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
    int actualWeapon = NO_WEAPON;
    uint8_t direction;
    float angle = 0;
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
    void equipWeapon(uint8_t weapon);
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
