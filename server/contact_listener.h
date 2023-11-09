#include "box2d/box2d.h"


class ContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) {

        Entity *entity = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	  
        if (entity != NULL) {
            if ((entity->entityType == WORM)) {;
                Worm *worm = (Worm*)entity;
                worm->startContact();
            }
        } 
        entity = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        if (entity != NULL) {
            if (entity->entityType == WORM) {
                Worm *worm = (Worm*)entity;
                worm->startContact();
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