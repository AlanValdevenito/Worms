#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "box2d/box2d.h"
#include "worm.h"
#include "red_grenade_fragment.h"

class ContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) {

        Entity *entity = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
        if (contact->GetFixtureA()->IsSensor()) {
            if (entity != NULL) {
                if ((entity->entityType == WORM)) {
                    Worm *worm = (Worm*)entity;
                    worm->startContact();
                } else if (entity->entityType == FRAGMENT) {
                    RedGrenadeFragment *fragment = (RedGrenadeFragment*)entity;
                    fragment->startContact();
                } else if (entity->entityType >= 2 && entity->entityType != FRAGMENT) {
                    entity->startContact();
                }
            } 
        }
        
        entity = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        if (contact->GetFixtureB()->IsSensor()) {
            if (entity != NULL) {
                if (entity->entityType == WORM) {
                    Worm *worm = (Worm*)entity;
                    worm->startContact();
                } else if (entity->entityType == FRAGMENT) {
                    RedGrenadeFragment *fragment = (RedGrenadeFragment*)entity;
                    fragment->startContact();
                } else if (entity->entityType >= 2 && entity->entityType != FRAGMENT) {
                    entity->startContact();
                }
            }
        }
    }
  
    void EndContact(b2Contact* contact) {
        Entity *entity = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
        if (contact->GetFixtureA()->IsSensor()) {
            if (entity != NULL) {
                if ((entity->entityType == WORM)) {
                    Worm *worm = (Worm*)entity;
                    worm->endContact();
                }
            }
        }
        entity = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        if (contact->GetFixtureB()->IsSensor()) {
            if (entity != NULL) {
                if (entity->entityType == WORM) {
                    Worm *worm = (Worm*)entity;
                    worm->endContact();
                }
            }
        }
    }
};
#endif