#ifndef PLAYER_H
#define PLAYER_H



#include <stdio.h>
#include <iostream>
#include <exception>
#include <list>
#include <vector>
#include <map>


class Player {
public:
    int playerId;
    int teamNumber;
    int actualWormId;
    std::vector<int> wormIds;
    int indexOfActualWorm;
    int numberOfAliveWorms;
    std::list<int> idsOfDeadWorms;
    std::map<int, bool> wormIsDeadById;
    bool isAlive = true;

    Player(int playerId, int teamNumber, std::vector<int> wormIds);
    int getId();
    int getActualWormId();
    int getTeamNumber();
    void changeActualWorm();
    void markWormAsDead(int wormId);

};
#endif