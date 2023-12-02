#ifndef WORM_H 
#define WORM_H

#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include "entity.h"
#include <map>
#include <string>
#include "yaml-cpp/yaml.h"
#include "constantes.h"


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
    bool infiniteHp;
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
