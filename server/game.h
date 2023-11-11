#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <iostream>
#include <exception>
#include <list>
#include <memory>

#include "box2d/box2d.h"
#include "world.h"
#include "server_protocol.h"
#include "thread.h"
#include "queue.h"
#include "broadcaster.h"
#include "constantes.h"
#include "dto.h"
#include "viga.h"
#include "gusano.h"
#include "player.h"
#include "green_grenade.h"

class Game : public Thread
{
private:
    Queue<std::shared_ptr<Dto>> &common_queue;
    Broadcaster &broadcaster;
    World world;
    //b2Body *body_w;
    std::vector<uint8_t> idPlayers;
    std::vector<Player> players;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::steady_clock::time_point timeOfAttack;
    bool wormAttacked;
    int numberOfPlayers;
    int numberOfWormsMoving = 0;
    int actualWormId;
    int indexOfActualPlayer = 0;
    //std::chrono::steady_clock::time_point t1;
    //std::chrono::steady_clock::time_point t2;
    // std::map<int, LISTA DE WORMS>;
    void mapa_rampa();
    void mapa_jaula();
    void mapa_puente();

public:
    GreenGrenade *greenGrenade = NULL;
    int idTurn;
    bool game_finished;
    Game(Queue<std::shared_ptr<Dto>> &queue, Broadcaster &broadcaster);
    void update();
    void run() override;
    void stop() override;
    void sendMap();
    void sendWorms();

    void moveWormLeft();
    void moveWormRight();
    void jumpWorm();
    void batWorm(int angle);
    void executeCommand(std::shared_ptr<Dto> dto);
    void broadcast();
    void createPlayers();
    void throwGreenGrenade(float angle, int power);
    void passTurn();
    void addPlayerId(uint8_t id);
    bool anyWormMoving();
    ~Game();
};
#endif
