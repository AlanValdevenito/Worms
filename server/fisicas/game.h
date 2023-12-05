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
#include "bazooka_rocket.h"
#include "banana.h"
#include "holy_grenade.h"
#include "dynamite.h"
#include "air_strike_rocket.h"
#include "red_grenade.h"
#include "red_grenade_fragment.h"
#include "mortero_rocket.h"
#include "entity.h"

class Game : public Thread
{
private:
    Queue<std::shared_ptr<Dto>> &common_queue;
    Broadcaster &broadcaster;
    std::map<std::string, int> config;
    World world;

    std::vector<uint8_t> idPlayers;
    std::vector<Player> players;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::steady_clock::time_point timeOfAttack;
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;

    float rate = 1000000000.0f / 30.0f; // en nanoseconds
    int rest = 0;
    int lost = 0;
    float timeStep = 1.0f / 30.0f;

    bool wormAttacked = false;
    int numberOfPlayers = 0;
    int numberOfWormsMoving = 0;
    int actualWormId = 0;
    int indexOfActualPlayer = 0;
    int numberOfAlivePlayers = 0;
    int jugadores_en_partida;
    GreenGrenade *greenGrenade = NULL;
    BazookaRocket *bazookaRocket = NULL;
    MorteroRocket *morteroRocket = NULL;
    Banana *banana = NULL;
    HolyGrenade *holyGrenade = NULL;
    Dynamite *dynamite = NULL;
    RedGrenade *redGrenade = NULL;
    std::vector<RedGrenadeFragment *> redGrenadeFragments;
    std::vector<AirStrikeRocket *> airStrike;
    std::vector<int> explodedFragmentIds;
    void mapa();
    void mapa_jaula();
    void mapa_puente();
    void mapa_real();
    void mapa_vigas_inclinadas();
    void finalizar_juego(std::shared_ptr<Dto> dto);
    bool timeIsUp();
    void beginNextTurn();
    void increaseHpOfTeamsWithLessPlayers();
    bool infiniteHp = false;
    bool endlessTurn = false;
    bool infiniteAmmunition = false;
    int idTurn = 1;
    void update();
    void updateWorms();
    void updatePlayers();
    void updateBombs();
    void limitFrameRate();
    
    void sendBombs();
    bool hayBombas();
    void moveWormLeft();
    void moveWormRight();
    void teleport(float x, float y);
    void jumpWorm(uint8_t direction);
    void batWorm(int angle);
    void executeCommand(std::shared_ptr<Dto> dto);
    void throwGreenGrenade(float angle, int power, int timeToExplotion);
    void throwRedGrenade(float angle, int power, int timeToExplotion);
    void shootHolyGrenade(float angle, int power, int timeToExplotion);
    void shootBanana(float angle, int power, int timeToExplotion);
    void shootDynamite(int timeToExplotion);
    void shootAirStrike(float x, float y);
    void passTurn();
    bool anyAirStrikeRocket();
    bool anyWormMoving();
    void shootBazooka(float angle, int power);
    void shootMortero(float angle, int power);
    void throwFragments(float x, float y);
public:
    void sendWorms();
    bool game_finished = false;
    Game(Queue<std::shared_ptr<Dto>> &queue, Broadcaster &broadcaster, int cantidad, int map);
    void run() override;
    void stop() override;
    void killPlayerWorms(uint8_t id);
    void sendMap();
    void createPlayers();
    void addPlayerId(uint8_t id);
    
    ~Game();
};
#endif
