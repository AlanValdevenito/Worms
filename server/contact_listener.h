#include "box2d/box2d.h"


class ContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) {
        std::cout << "begin contact\n";

        Entity *entity = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	  
        if (entity != NULL) {
            //int type = entity->getEntityType();
            std::cout << "entity A != NULL\n";
            if ((entity->entityType == WORM)) {
                std::cout << "entity A es WoRM\n";
                Worm *worm = (Worm*)entity;
                worm->startContact();
            } else if (entity->entityType == BEAM) {
                std::cout << "entity A es BEAM\n";
            } else {
                std::cout << "entityType de A = " << (int)entity->entityType << "\n";
            }
        } 
        entity = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        if (entity != NULL) {
            //int type = entity->getEntityType();
            std::cout << "entity B != NULL\n";
            if (entity->entityType == WORM) {
                std::cout << "entity B es WoRM\n";
                Worm *worm = (Worm*)entity;
                worm->startContact();
            } else if (entity->entityType == BEAM) {
                std::cout << "entity B es BEAM\n";
            } else {
                std::cout << "entityType de B = " << (int)entity->entityType << "\n";
            }
        }
    }
  
    void EndContact(b2Contact* contact) {
        std::cout << "end contact\n";
        Entity *entity = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	  
        if (entity != NULL) {
            //int type = entity->getEntityType();
            std::cout << "entity A != NULL\n";
            if ((entity->entityType == WORM)) {
                std::cout << "entity A es WoRM\n";
                Worm *worm = (Worm*)entity;
                worm->endContact();
            } else if (entity->entityType == BEAM) {
                std::cout << "entity A es BEAM\n";
            } else {
                std::cout << "entityType de A = " << (int)entity->entityType << "\n";
            }
        } 
        entity = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        if (entity != NULL) {
            //int type = entity->getEntityType();
            std::cout << "entity B != NULL\n";
            if (entity->entityType == WORM) {
                std::cout << "entity B es WoRM\n";
                Worm *worm = (Worm*)entity;
                worm->endContact();
            } else if (entity->entityType == BEAM) {
                std::cout << "entity B es BEAM\n";
            } else {
                std::cout << "entityType de B = " << (int)entity->entityType << "\n";
            }
        }
    }
};