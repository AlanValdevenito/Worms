#include "box2d/box2d.h"
#include <list>
#include <cmath>
#include "entity.h"

class Worm : public Entity {
private:
    b2Body *body;
    
    float x;
    float y;
    uint8_t id;
    uint8_t teamNumber;
    uint8_t hp;
    

public:
    bool facingRight;
    bool is_alive;
    uint8_t damageTaken;
    bool isRunning;
    uint8_t playerId = -1;
    EntityType entityType = WORM;
    int numberOfContacts = 0;
    Worm(b2World *b2world, float x, float y, uint8_t id);
    float getXCoordinate();
    float getYCoordinate();
    uint8_t getId();
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
