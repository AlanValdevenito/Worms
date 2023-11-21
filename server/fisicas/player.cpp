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
    // std::cout << "Player::changeActualWorm()\n";

    // std::cout << "wormIds = [";
    // for (int i = 0; i < (int)wormIds.size(); i++) {
        // std::cout << (int)wormIds[i] << ", ";
    // }
    // std::cout << "]\n";

    if (indexOfActualWorm == (int)wormIds.size() - 1) {
        indexOfActualWorm = 0;
    } else {
        indexOfActualWorm++;
    }
    actualWormId = wormIds[indexOfActualWorm];
    for (int wormId : idsOfDeadWorms) {
        if (wormId == actualWormId) changeActualWorm();
    }
    // std::cout << "actualWormId = " << actualWormId << "\n";
}

int Player::getTeamNumber() {
    return teamNumber;
}


void Player::markWormAsDead(int wormId) {
    std::cout << "wormId " << wormId << " is dead\n";  
    idsOfDeadWorms.push_back(wormId);
}