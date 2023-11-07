#ifndef PLAYER_H
#define PLAYER_H



#include <stdio.h>
#include <iostream>
#include <exception>
#include <list>
#include <vector>


class Player {
public:
    int playerId;
    int teamNumber;
    int actualWormId;
    std::vector<int> wormIds;
    int indexOfActualWorm;
    int numberOfAliveWorms;
    

    Player(int playerId, int teamNumber, std::vector<int> wormIds);
    int getId();
    int getActualWormId();
    int getTeamNumber();
    void changeActualWorm();

};
#endif