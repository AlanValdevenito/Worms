#include "player.h"


Player::Player(int playerId, int teamNumber, std::vector<int> wormIds) : 
    playerId(playerId),
    teamNumber(teamNumber),
    actualWormId(wormIds[0]),
    wormIds(wormIds),
    indexOfActualWorm(0),
    numberOfAliveWorms((int)wormIds.size()) {
        for (int wormId : wormIds) {
            wormIsDeadById[wormId] = false;
        }
    }


int Player::getId() {
    return playerId;
}

int Player::getActualWormId() {
    return actualWormId;
}

void Player::changeActualWorm() {
    std::cout << "wormIds = [";
    for (int i = 0; i < (int)wormIds.size(); i++) {
        std::cout << (int)wormIds[i] << ", ";
    }
    std::cout << "]\n";
    std::cout << "Player::changeActualWorm, numberOfAliveWorms = " << numberOfAliveWorms << "\n";
    for (int i = 0; i < (int)wormIds.size(); i++) {
        if (indexOfActualWorm == (int)wormIds.size() - 1) {
            indexOfActualWorm = 0;
        } else {
            indexOfActualWorm++;
        }
        actualWormId = wormIds[indexOfActualWorm];
        if (not wormIsDeadById[actualWormId]) return;
    }
}

int Player::getTeamNumber() {
    return teamNumber;
}


void Player::markWormAsDead(int wormId) {
    wormIsDeadById[wormId] = true;
}