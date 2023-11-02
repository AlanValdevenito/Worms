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
    int actualWormId;
    std::vector<int> wormIds;
    int indexOfActualWorm;

    Player(int playerId, std::vector<int> wormIds);
    int getId();
    int getActualWormId();
    void changeActualWorm();
};
#endif