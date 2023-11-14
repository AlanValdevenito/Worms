#include "box2d/box2d.h"
//#include "bazooka_rocket.h"

//class BazookaRocket;

class ContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) {

        Entity *entity = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	  
        if (entity != NULL) {
            if ((entity->entityType == WORM)) {
                Worm *worm = (Worm*)entity;
                worm->startContact();
            } else if (entity->entityType == BAZOOKA_ROCKET) {
                entity->startContact();
                //BazookaRocket *bazookaRocket = (BazookaRocket*)entity;
                //bazookaRocket->startContact();
            }
        } 
        entity = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        if (entity != NULL) {
            if (entity->entityType == WORM) {
                Worm *worm = (Worm*)entity;
                worm->startContact();
            } else if (entity->entityType == BAZOOKA_ROCKET) {
                entity->startContact();
                //BazookaRocket *bazookaRocket = (BazookaRocket*)entity;
                //bazookaRocket->startContact();
            }
        }
    }
  
    void EndContact(b2Contact* contact) {
        Entity *entity = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	  
        if (entity != NULL) {
            if ((entity->entityType == WORM)) {
                Worm *worm = (Worm*)entity;
                worm->endContact();
            }
        } 
        entity = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        if (entity != NULL) {
            if (entity->entityType == WORM) {
                Worm *worm = (Worm*)entity;
                worm->endContact();
            }
        }
    }
};