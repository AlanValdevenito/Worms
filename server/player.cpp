#include "player.h"


Player::Player(int playerId, int teamNumber, std::vector<int> wormIds) : 
    playerId(playerId),
    teamNumber(teamNumber),
    actualWormId(wormIds[0]),
    wormIds(wormIds),
    indexOfActualWorm(0),
    numberOfAliveWorms((int)wormIds.size()) {}


int Player::getId() {
    return playerId;
}

int Player::getActualWormId() {
    return actualWormId;
}

void Player::changeActualWorm() {
    if (indexOfActualWorm == (int)wormIds.size() - 1) {
        indexOfActualWorm = 0;
    } else {
        indexOfActualWorm++;
    }
    actualWormId = wormIds[indexOfActualWorm];
}

int Player::getTeamNumber() {
    return teamNumber;
}