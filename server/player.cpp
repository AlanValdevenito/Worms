#include "player.h"


Player::Player(int playerId, std::vector<int> wormIds) : 
    playerId(playerId),
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