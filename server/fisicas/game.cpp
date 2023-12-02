#include "game.h"
#include <chrono>
#include <thread>

#define TURN_DURATION 60
#define TIME_LEFT_AFTER_ATTACK 2
#define WATER_POSITION 0



std::map<std::string, int> loadConfig(const std::string configFileName)
{
    YAML::Node yaml = YAML::LoadFile(configFileName);
    std::map<std::string, int> config;
    config["map"] = yaml["map"].as<int>();
    config["wormHp"] = yaml["worm"]["hp"].as<int>();
    config["wormExtraHp"] = yaml["worm"]["extra_hp"].as<int>();
    config["wormSpeed"] = yaml["worm"]["speed"].as<int>();
    config["turnDuration"] = yaml["turn_duration"].as<int>();
    config["timeLeftAfterAttack"] = yaml["time_left_after_attack"].as<int>();

    config["dynamiteDamage"] = yaml["dynamite"]["damage"].as<int>();
    config["dynamiteRadius"] = yaml["dynamite"]["radius"].as<int>();
    config["dynamiteAmmunition"] = yaml["dynamite"]["ammunition"].as<int>();

    config["greenGrenadeDamage"] = yaml["green_grenade"]["damage"].as<int>();
    config["greenGrenadeRadius"] = yaml["green_grenade"]["radius"].as<int>();
    config["greenGrenadeAmmunition"] = yaml["green_grenade"]["ammunition"].as<int>();

    config["redGrenadeDamage"] = yaml["red_grenade"]["damage"].as<int>();
    config["redGrenadeRadius"] = yaml["red_grenade"]["radius"].as<int>();
    config["redGrenadeAmmunition"] = yaml["red_grenade"]["ammunition"].as<int>();

    config["bazookaDamage"] = yaml["bazooka"]["damage"].as<int>();
    config["bazookaRadius"] = yaml["bazooka"]["radius"].as<int>();
    config["bazookaAmmunition"] = yaml["bazooka"]["ammunition"].as<int>();

    config["morteroDamage"] = yaml["mortero"]["damage"].as<int>();
    config["morteroRadius"] = yaml["mortero"]["radius"].as<int>();
    config["morteroAmmunition"] = yaml["mortero"]["ammunition"].as<int>();

    config["bananaDamage"] = yaml["banana"]["damage"].as<int>();
    config["bananaRadius"] = yaml["banana"]["radius"].as<int>();
    config["bananaAmmunition"] = yaml["banana"]["ammunition"].as<int>();
    
    config["holyGrenadeDamage"] = yaml["holy_grenade"]["damage"].as<int>();
    config["holyGrenadeRadius"] = yaml["holy_grenade"]["radius"].as<int>();
    config["holyGrenadeAmmunition"] = yaml["holy_grenade"]["ammunition"].as<int>();

    config["airStrikeDamage"] = yaml["air_strike"]["damage"].as<int>();
    config["airStrikeRadius"] = yaml["air_strike"]["radius"].as<int>();
    config["airStrikeAmmunition"] = yaml["air_strike"]["ammunition"].as<int>();

    config["teleportAmmunition"] = yaml["teleport"]["ammunition"].as<int>();
    config["cantidad_de_worms"] = yaml["cantidad_de_worms"].as<int>();
    return config;
}

Game::Game(Queue<std::shared_ptr<Dto>> &queue, Broadcaster &broadcaster, int cantidad, int map) : common_queue(queue),
                                                                                         broadcaster(broadcaster),
                                                                                         config(loadConfig("../configuracion.yml")),
                                                                                         world(World(config)),
                                                                                         jugadores_en_partida(cantidad),
                                                                                         game_finished(false)

{   
    if (map == 1)
    {
        mapa();
    }
    else if (map == 2)
    {
        mapa_jaula();
    }
    else if (map == 3)
    {
        mapa_puente();
    }
    else
    {
        mapa_vigas_inclinadas();
    }
}

void Game::mapa()
{

    /******************** VIGAS ********************/

    // Piso 0
    int x = 5;
    for (int i = 0; i < 10; i++)
    {
        world.addBeam(x, 5, 0, LONG);
        x += 6;
    }

    // Piso 1
    x = 5;
    for (int i = 0; i < 10; i++)
    {

        if (x == 53)
        {
            x += 6;
            continue;
        }

        world.addBeam(x, 10, 0, LONG);
        x += 6;
    }

    // Piso 2
    x = 5;
    for (int i = 0; i < 10; i++)
    {

        if (x == 11)
        {
            x += 6;
            continue;
        }

        world.addBeam(x, 15, 0, LONG);
        x += 6;
    }

    // Piso 3
    x = 5;
    for (int i = 0; i < 10; i++)
    {

        if (x == 53)
        {
            x += 6;
            continue;
        }

        world.addBeam(x, 20, 0, LONG);
        x += 6;
    }

    // Piso 4
    x = 5;
    for (int i = 0; i < 10; i++)
    {

        if (x == 11)
        {
            x += 6;
            continue;
        }

        world.addBeam(x, 25, 0, LONG);
        x += 6;
    }

    // Techo
    x = 5;
    for (int i = 0; i < 10; i++)
    {
        world.addBeam(x, 29.7, 0, LONG);
        x += 6;
    }

    // Paredes
    float y = 8.4;
    for (int i = 0; i < 4; i++)
    {
        world.addBeam(2.4f, y, 90, LONG);
        y += 6;
    }

    y = 8.4;
    for (int i = 0; i < 4; i++)
    {
        world.addBeam(61.6, y, 90, LONG);
        y += 6;
    }

    // Rampa del piso 4 al piso 3
    world.addBeam(8.8, 24.2, 135, SHORT);
    world.addBeam(10.8, 22.2, 135, SHORT);
    world.addBeam(11.8, 21.2, 135, SHORT);

    // Rampa del piso 3 al piso 2
    world.addBeam(55.2, 19.2, 45, SHORT);
    world.addBeam(53.2, 17.2, 45, SHORT);
    world.addBeam(52.2, 16.2, 45, SHORT);

    // Rampa del piso 2 al piso 1
    world.addBeam(8.8, 14.2, 135, SHORT);
    world.addBeam(10.8, 12.2, 135, SHORT);
    world.addBeam(11.8, 11.2, 135, SHORT);

    // Rampa del piso 1 al piso 0
    world.addBeam(55.2, 9.2, 45, SHORT);
    world.addBeam(53.2, 7.2, 45, SHORT);
    world.addBeam(52.2, 6.2, 45, SHORT);

    /******************** WORMS ********************/

    x = 20;
    for (int i = 0; i < config["cantidad_de_worms"]; i++)
    {
        world.addWorm(x, 22);
        x += 2;
    }
}

void Game::mapa_jaula()
{

    /******************** VIGAS ********************/

    // Piso
    world.addBeam(5, 5, 0, LONG);  // 2 3 4 5 6 7 8
    world.addBeam(11, 5, 0, LONG); // 8 9 10 11 12 13 14
    world.addBeam(17, 5, 0, LONG); // 14 15 16 17 18 19 20
    world.addBeam(23, 5, 0, LONG); // 20 21 22 23 24 25 26

    // Techo
    world.addBeam(5, 17.8f, 0, LONG);
    world.addBeam(11, 17.8f, 0, LONG);
    world.addBeam(17, 17.8f, 0, LONG);
    world.addBeam(23, 17.8f, 0, LONG);

    // Paredes
    world.addBeam(2.4f, 8.4f, 90, LONG);
    world.addBeam(2.4f, 14.4f, 90, LONG);
    world.addBeam(25.6f, 8.4f, 90, LONG);
    world.addBeam(25.6f, 14.4f, 90, LONG);

    /******************** WORMS ********************/

    int x = 5;
    for (int i = 0; i < config["cantidad_de_worms"]; i++)
    {
        world.addWorm(x, 10);
        x += 2;
    }
}

void Game::mapa_puente()
{

    /******************** VIGAS ********************/

    world.addBeam(2.4f, 8.4f, 90, LONG);

    world.addBeam(5, 5, 0, LONG);  // 2 3 4 5 6 7 8
    world.addBeam(11, 5, 0, LONG); // 8 9 10 11 12 13 14
    world.addBeam(17, 5, 0, LONG); // 14 15 16 17 18 19 20
    world.addBeam(23, 5, 0, LONG); // 20 21 22 23 24 25 26
    world.addBeam(29, 5, 0, LONG);
    world.addBeam(34, 5, 0, LONG);

    world.addBeam(36.6f, 8.4f, 90, LONG);

    /******************** WORMS ********************/

    int x = 3;
    for (int i = 0; i < config["cantidad_de_worms"]; i++)
    {
        world.addWorm(x, 7);
        x += 2;
    }
}

void Game::mapa_vigas_inclinadas()
{

    /******************** VIGAS ********************/

    world.addBeam(3, 9, 0, LONG);
    world.addBeam(11.2f, 10, 0, LONG);
    world.addBeam(18.7f, 11.9f, 0, LONG);

    world.addBeam(7.2f, 9.5f, 22.5f, SHORT);
    world.addBeam(15, 11, 45, SHORT);
    world.addBeam(22, 13.2f, 67.5f, SHORT);

    /******************** WORMS ********************/

    int x = 3;
    for (int i = 0; i < config["cantidad_de_worms"]; i++)
    {
        world.addWorm(x, 14);
        x += 2;
    }
}


void Game::createPlayers()
{
    int playerIndex = 0;
    int wormId = 1;
    int numberOfWorms = (int)world.getWorms().size();
    std::map<int, std::vector<int>> wormIdsByPlayerId;
    for(int i = 0; i < numberOfWorms; i++) {
        if(playerIndex == (int)idPlayers.size())
            playerIndex = 0;

        world.getWormsById()[wormId]->setPlayerId(idPlayers[playerIndex]);
        world.getWormsById()[wormId]->setTeamNumber(playerIndex);
        wormIdsByPlayerId[idPlayers[playerIndex]].push_back(wormId);
        wormId++;    
        playerIndex++;
    }


    int teamNumber = 0;
    for(int playerId : idPlayers) {
        players.push_back(Player(playerId, teamNumber, wormIdsByPlayerId[playerId]));
        teamNumber++;
    }


    idTurn = idPlayers[indexOfActualPlayer];
    actualWormId = players[indexOfActualPlayer].actualWormId;
    numberOfPlayers = (int)idPlayers.size();
    numberOfAlivePlayers = numberOfPlayers;

    // si la cantidad de gusanos no es multiplo de la cantidad de jugadores
    if (numberOfWorms % numberOfPlayers != 0) {
        increaseHpOfTeamsWithLessPlayers();
    }
}

void Game::increaseHpOfTeamsWithLessPlayers() {
    int maxNumberOfWorms = 0;
    // busco cual es la cantidad maxima de gusanos por equipo
    for (int i = 0; i < numberOfPlayers; i++) {
        if (players[i].numberOfAliveWorms > maxNumberOfWorms) {
            maxNumberOfWorms = players[i].numberOfAliveWorms;
        }
    }

    // a los equipos que tienen menos gusanos que la cantidad maxima
    // les sumo hp 
    for (int i = 0; i < numberOfPlayers; i++) {
        if (players[i].numberOfAliveWorms < maxNumberOfWorms) {
            for (int wormId : players[i].wormIds) {
                world.getWormsById()[wormId]->increaseHp(config["wormExtraHp"]);
            }
        }
    }
}

void Game::finalizar_juego(std::shared_ptr<Dto> dto)
{
    broadcaster.notificarCierre(dto);
    broadcaster.deleteAllQueues(); // aviso a los demas que cierren
    stop();
}

void Game::run()
{
    begin = std::chrono::steady_clock::now();
    while (not game_finished)
    {
        world.step(timeStep + ((float)lost) / 1000000000.0f);
        std::shared_ptr<Dto> dto;
        if (common_queue.try_pop(dto))
        {

            if (dto->is_alive() && dto->return_code() == FINALIZAR_CODE)
            {
                broadcaster.removeQueueWithId(dto->get_cliente_id()); // elimino la queue del cliente que murio
                jugadores_en_partida -= 1;
                if (jugadores_en_partida == 1) // si solo queda un jugador
                {
                    finalizar_juego(dto);
                    break;
                }
            }
            executeCommand(dto);
        }
        update();
        limitFrameRate();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
        // broadcast();
    }
}

void Game::addPlayerId(uint8_t id)
{
    idPlayers.push_back(id);
}

bool Game::timeIsUp() {
    end = std::chrono::steady_clock::now();
    int timeSinceTurnStarted = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
    int timeSinceWormAttacked = std::chrono::duration_cast<std::chrono::seconds>(end - timeOfAttack).count();
    return timeSinceTurnStarted >= config["turnDuration"] ||
           (wormAttacked && timeSinceWormAttacked >= config["timeLeftAfterAttack"]);
}

void Game::beginNextTurn() {
    //world.getWormsById()[actualWormId]->equipWeapon(NO_WEAPON);
    
    
    
    for (int i = 0; i < numberOfPlayers; i++)
    {
        if (indexOfActualPlayer == (int)idPlayers.size() - 1)
        {
            indexOfActualPlayer = 0;
        }
        else
        {
            indexOfActualPlayer++;
        }
        if (players[indexOfActualPlayer].isAlive)
        {
            idTurn = idPlayers[indexOfActualPlayer];
            players[indexOfActualPlayer].changeActualWorm();
            actualWormId = players[indexOfActualPlayer].actualWormId;
            world.getWormsById()[actualWormId]->equipWeapon(SIN_ARMA);
            begin = std::chrono::steady_clock::now();
            wormAttacked = false;
            return;
        }
    }
    // si no hay un player
    idTurn = -1;
}

void Game::passTurn()
{
    // cambio de turno
    if (endlessTurn) return;
    if (timeIsUp())
    {
        if (world.anyMovement() || hayBombas())
        {
            idTurn = -1;
            return;
        }
        // cuando al gusano se le termina el turno, le saco el arma.
        
        updateWorms();
        updatePlayers();
        if (not wormAttacked) {
            world.getWormsById()[actualWormId]->equipWeapon(SIN_ARMA);
        }
        beginNextTurn();
        if (idTurn == -1) {
            // si no hay jugadores para elegir ==> cierro.
            broadcaster.notificarCierre(std::make_shared<Dto>(FINALIZAR_CODE, 1));
            broadcaster.deleteAllQueues(); // aviso a los demas que cierren
            stop();
            return;
        }
    }
}

void Game::limitFrameRate()
{
    t2 = std::chrono::steady_clock::now();
    rest = (int)rate - std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    if (rest < 0)
    {
        t1 = t1 - std::chrono::nanoseconds((int)rest); // - rest es positivo
        lost = -rest;
    }
    else
    {
        lost = 0;
        std::this_thread::sleep_for(std::chrono::nanoseconds((int)rest));
    }
    t1 = t1 + std::chrono::nanoseconds((int)rate);
}

void Game::updateWorms()
{
    // actualizo los gusanos
    for (Worm *worm : world.getWorms())
    {   
        if (worm->is_alive && worm->numberOfContacts > 0 && not worm->isMoving() && worm->getState() != EQUIPANDO_ARMA) {
            worm->state = QUIETO;
        }
        if (worm->is_alive && worm->numberOfContacts == 0 && 
            worm->getState() != SALTANDO_ATRAS && worm->getState() != SALTANDO_ADELANTE &&
            worm->getState() != GOLPEADO && worm->getVelocity().y < 0.0f) {worm->state = CAYENDO;}
        if (not worm->isMoving() && worm->getHp() == 0 && worm->is_alive)
        {
            worm->is_alive = false;
            begin = std::chrono::steady_clock::now();

            players[worm->playerId - 1].numberOfAliveWorms--;
            players[worm->playerId - 1].markWormAsDead(worm->getId());
        }
        // si el worm sufre algun daño en su turno pierde el turno
        if (worm->getId() == actualWormId && not wormAttacked && worm->damageTaken > 0) {
            if (not endlessTurn) {
                beginNextTurn();
            }
            
        }

        if (worm->getYCoordinate() <= WATER_POSITION && worm->is_alive)
        {
            worm->takeDamage(worm->getHp());
            worm->getBody()->SetLinearVelocity(b2Vec2(0, 0));
            worm->getBody()->SetTransform(b2Vec2(worm->getXCoordinate(), worm->getYCoordinate()), true);
        }
        if (not world.anyMovement())
        {   
            if (not infiniteHp) {
                worm->makeDamage();
            }
            if (worm->getState() == MUERTO && actualWormId == worm->getId() && worm->is_alive)
            {
                players[worm->playerId - 1].markWormAsDead(worm->getId());
                
                if (endlessTurn) {
                    beginNextTurn();
                }
            }
        }

        if (worm->numberOfContacts == 0)
        {
            if (worm->getYCoordinate() > worm->highestYCoordinateReached)
            {
                worm->highestYCoordinateReached = worm->getYCoordinate();
            }
        }

        if (worm->jumpTimeout > 0)
            worm->jumpTimeout--;
        if (worm->state == GOLPEADO)
        {
            worm->updateAngle();
        }
    }
}

void Game::updatePlayers()
{
    // actualizo los players
    for (int i = 0; i < numberOfPlayers; i++)
    {
        // si un player tiene 0 worms => pierde
        if (players[i].numberOfAliveWorms == 0 && players[i].isAlive)
        {
            players[i].isAlive = false;
            numberOfAlivePlayers--;
        }
        // si queda 1 player vivo o menos => se termina el match
        if (numberOfAlivePlayers <= 1)
        {
            uint8_t winnerId;
            for (Player player : players)
            {
                // el player vivo es el ganador
                if (player.isAlive)
                {
                    winnerId = player.getId();
                    // notifico el ganador
                    std::shared_ptr<Ganador> ganador = std::make_shared<Ganador>(winnerId);
                    broadcaster.AddDtoToQueues(ganador);
                    break;
                }
            }
            broadcaster.notificarCierre(std::make_shared<Dto>(FINALIZAR_CODE, 1));
            broadcaster.deleteAllQueues(); // aviso a los demas que cierren
            stop();
            return;
        }
    }
}

void Game::updateBombs()
{
    if (greenGrenade != NULL) {
        if (greenGrenade->exploded) {
            greenGrenade->destroy();
            delete greenGrenade;
            greenGrenade = NULL;
        } else {
            greenGrenade->update();
        }
        
    }

    if (bazookaRocket != NULL)
    {
        if (bazookaRocket->exploded) { 
            bazookaRocket->destroy();
            delete bazookaRocket;
            bazookaRocket = NULL;
        } else {
            bazookaRocket->updateAngle();
        }
    }

    if (banana != NULL)
    {
        if (banana->exploded) {
            banana->destroy();
            delete banana;
            banana = NULL;
        } else {
            banana->update();
        }
    }

    if (holyGrenade != NULL)
    {   
        if (holyGrenade->exploded)
        {
            holyGrenade->destroy();
            delete holyGrenade;
            holyGrenade = NULL;
        } else {
            holyGrenade->update();
        }
        
    }

    if (dynamite != NULL)
    {   
        if (dynamite->exploded)
        {
            dynamite->destroy();
            delete dynamite;
            dynamite = NULL;
        } else {
            dynamite->update();
        }
        
    }
    if (redGrenade != NULL) {
        if (redGrenade->exploded) {
            float x = redGrenade->getXCoordinate();
            float y = redGrenade->getYCoordinate() + 1;
            throwFragments(x, y);
            redGrenade->destroy();
            delete redGrenade;
            redGrenade = NULL;
        } else {
            redGrenade->update();
        }
        
    }
    if (morteroRocket != NULL) {   
        if (morteroRocket->exploded) {   
            float x = morteroRocket->getXCoordinate();
            float y = morteroRocket->getYCoordinate() + 1;
            throwFragments(x, y);
            morteroRocket->destroy();
            delete morteroRocket;
            morteroRocket = NULL;
        } else {
            morteroRocket->updateAngle();
        }
    }

    for (int i = 0; i < (int)redGrenadeFragments.size(); i++) {
        if (redGrenadeFragments[i] != NULL) {
            if (redGrenadeFragments[i]->exploded) {   
                redGrenadeFragments[i]->destroy();
                delete redGrenadeFragments[i];
                redGrenadeFragments[i] = NULL;
            }
        }
    }

    for (int i = 0; i < (int)airStrike.size(); i++) {
        if (airStrike[i] != NULL) {
            if (airStrike[i]->exploded) {
                airStrike[i]->destroy();
                delete airStrike[i];
                airStrike[i] = NULL;
            }
        }
        
    }


}

void Game::update()
{
    updateWorms();
    updatePlayers();
    if (game_finished)
        return;
    
    sendWorms();
    updateBombs();
    passTurn();
}

bool Game::anyAirStrikeRocket()
{
    for (AirStrikeRocket *rocket : airStrike)
    {
        if (rocket != NULL)
        {

            if (not rocket->exploded)
            {
                return true;
            }
        }
    }
    return false;
}

bool Game::hayBombas()
{
    if (greenGrenade != NULL || banana != NULL || dynamite != NULL ||
        bazookaRocket != NULL || holyGrenade != NULL || redGrenade != NULL || morteroRocket != NULL)
    {
        return true;
    }
    for (AirStrikeRocket *rocket : airStrike)
    {
        if (rocket != NULL)
        {
            return true;
        }
    }
    for (RedGrenadeFragment *fragment : redGrenadeFragments)
    {
        if (fragment != NULL)
        {
            return true;
        }
    }
    return false;
}

void Game::sendWorms()
{

    std::vector<std::shared_ptr<Gusano>> vectorGusanos;
    for (Worm *w : world.getWorms())
    {   
        if (w->is_alive)
         {
            std::shared_ptr<Gusano> g = std::make_shared<Gusano>((w->getId()),
                                                                 (int)(w->getXCoordinate() * 100),
                                                                 (int)(w->getYCoordinate() * 100),
                                                                 w->getHp(),
                                                                 w->getTeamNumber(),
                                                                 w->getState(),
                                                                 w->getWeapon(),
                                                                 w->getDirection(),
                                                                 (uint8_t)w->getAngle());
            vectorGusanos.push_back(g);
        }
    }
    std::shared_ptr<Gusanos> gusanos = std::make_shared<Gusanos>(vectorGusanos);

    int id = players[indexOfActualPlayer].getActualWormId(); // obtengo el id del gusano actual
    gusanos->set_gusano_de_turno(id);
    
    if (hayBombas())
    {
        gusanos->set_flag_proyectil(true);
    }

    broadcaster.AddDtoToQueues(gusanos);
    // crear granada
    if (hayBombas()) {
        sendBombs();
    }
}

void Game::sendBombs() {
    std::vector<std::shared_ptr<Proyectil>> proyectiles;
    if (greenGrenade != NULL) {
        std::shared_ptr<GranadaVerde> granada = std::make_shared<GranadaVerde>((uint16_t)(greenGrenade->getXCoordinate() * 100), (uint16_t)(greenGrenade->getYCoordinate() * 100), (uint8_t)(greenGrenade->getAngle()), greenGrenade->exploded, greenGrenade->getTimeLeftToExplode());
        proyectiles.push_back(granada);
    }

    if (redGrenade != NULL) {
        std::shared_ptr<GranadaRoja> granadaRoja = std::make_shared<GranadaRoja>((uint16_t)(redGrenade->getXCoordinate() * 100), (uint16_t)(redGrenade->getYCoordinate() * 100), (uint8_t)(redGrenade->getAngle()), redGrenade->exploded, redGrenade->getTimeLeftToExplode());
        proyectiles.push_back(granadaRoja);
    }

    if (bazookaRocket != NULL) {
        std::shared_ptr<Bazuka> bazooka = std::make_shared<Bazuka>((uint16_t)(bazookaRocket->getXCoordinate() * 100), (uint16_t)(bazookaRocket->getYCoordinate() * 100), (uint16_t)(bazookaRocket->getAngle()), bazookaRocket->dir, bazookaRocket->exploded);
        proyectiles.push_back(bazooka);
    }

    if (banana != NULL)
    {
        std::shared_ptr<GranadaBanana> granadaBanana = std::make_shared<GranadaBanana>((uint16_t)(banana->getXCoordinate() * 100), (uint16_t)(banana->getYCoordinate() * 100), (uint8_t)(banana->getAngle()), banana->exploded, banana->getTimeLeftToExplode());
        proyectiles.push_back(granadaBanana);
    }

    if (holyGrenade != NULL)
    {
        std::shared_ptr<GranadaSanta> granadaSanta = std::make_shared<GranadaSanta>((uint16_t)(holyGrenade->getXCoordinate() * 100), (uint16_t)(holyGrenade->getYCoordinate() * 100), (uint8_t)holyGrenade->getAngle(), holyGrenade->exploded, holyGrenade->getTimeLeftToExplode());
        proyectiles.push_back(granadaSanta);
    }

    if (dynamite != NULL)
    {
        std::shared_ptr<Dinamita> dinamita = std::make_shared<Dinamita>((uint16_t)(dynamite->getXCoordinate() * 100), (uint16_t)(dynamite->getYCoordinate() * 100), dynamite->exploded, dynamite->getTimeLeftToExplode());
        proyectiles.push_back(dinamita);
    }

    if (morteroRocket != NULL)
    {
        std::shared_ptr<Mortero> mortero = std::make_shared<Mortero>((uint16_t)(morteroRocket->getXCoordinate() * 100), (uint16_t)(morteroRocket->getYCoordinate() * 100), (uint16_t)(morteroRocket->getAngle()), morteroRocket->dir, morteroRocket->exploded);
        proyectiles.push_back(mortero);
    }

    int id_proyectil = 1;
    for (int i = 0; i < (int)airStrike.size(); i++)
    {
        if (airStrike[i] != NULL)
        {
            std::shared_ptr<Misil> misil = std::make_shared<Misil>(id_proyectil, (uint16_t)(airStrike[i]->getXCoordinate() * 100), (uint16_t)(airStrike[i]->getYCoordinate() * 100), airStrike[i]->exploded);
            proyectiles.push_back(misil);
        }
        id_proyectil++;
    }

    int id_fragmento = 1;
    for (int i = 0; i < (int)redGrenadeFragments.size(); i++)
    {
        if (redGrenadeFragments[i] != NULL)
        {   
            std::shared_ptr<Fragmento> fragmento = std::make_shared<Fragmento>(id_fragmento, (uint16_t)(redGrenadeFragments[i]->getXCoordinate() * 100), (uint16_t)(redGrenadeFragments[i]->getYCoordinate() * 100), 0, redGrenadeFragments[i]->exploded);
            proyectiles.push_back(fragmento);
        }
        id_fragmento++;
    }

    if (proyectiles.size() > 0)
    {
        std::shared_ptr<Proyectiles> ps = std::make_shared<Proyectiles>(proyectiles);
        broadcaster.AddDtoToQueues(ps);
    }
}


void Game::sendMap()
{
    std::vector<std::shared_ptr<Viga>> vs;
    for (auto &beam : world.getBeams())
    {
        std::shared_ptr<Viga> viga = std::make_shared<Viga>((int)(beam.getXCoordinate() * 100),
                                                            (int)(beam.getYCoordinate() * 100),
                                                            (int)(beam.getWidth() * 100),
                                                            (int)(beam.getHeight() * 100),
                                                            (int)(beam.getAngle()));

        vs.push_back(viga);
    }
    std::shared_ptr<Vigas> vigas = std::make_shared<Vigas>(vs);
    broadcaster.AddDtoToQueues(vigas);
}

void Game::moveWormRight()
{
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->moveRight();
}

void Game::moveWormLeft()
{
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->moveLeft();
}

void Game::jumpWorm(uint8_t direction)
{
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    if (direction == 0)
    {
        world.getWormsById()[idActualWorm]->jump();
    }
    else
    {
        world.getWormsById()[idActualWorm]->jumpBackward();
    }
}

void Game::batWorm(int angle)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->bat(world.getWorms(), angle);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::stop()
{
    game_finished = true;
}

void Game::throwGreenGrenade(float angle, int power, int timeToExplotion)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    greenGrenade = new GreenGrenade(&world.world, actualWorm->getXCoordinate(),
                                    actualWorm->getYCoordinate(),
                                    timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    greenGrenade->shoot(direction, angle, power);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}

void Game::throwRedGrenade(float angle, int power, int timeToExplotion)
{
    if (wormAttacked && not endlessTurn)
        return;

    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    redGrenade = new RedGrenade(&world.world, actualWorm->getXCoordinate(),
                                actualWorm->getYCoordinate(),
                                timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    redGrenade->shoot(direction, angle, power);
    redGrenadeFragments.clear();
    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}

void Game::shootBazooka(float angle, int power)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    bazookaRocket = new BazookaRocket(&world.world, actualWorm->getXCoordinate(),
                                      actualWorm->getYCoordinate(), angle, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    bazookaRocket->shoot(direction, angle, power);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}

void Game::shootMortero(float angle, int power)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    morteroRocket = new MorteroRocket(&world.world, actualWorm->getXCoordinate(),
                                      actualWorm->getYCoordinate(), angle, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    morteroRocket->shoot(direction, angle, power);
    redGrenadeFragments.clear();
    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}

void Game::shootBanana(float angle, int power, int timeToExplotion)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    banana = new Banana(&world.world, actualWorm->getXCoordinate(),
                        actualWorm->getYCoordinate(),
                        timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    banana->shoot(direction, angle, power);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}

void Game::shootHolyGrenade(float angle, int power, int timeToExplotion)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    holyGrenade = new HolyGrenade(&world.world, actualWorm->getXCoordinate(),
                                  actualWorm->getYCoordinate(),
                                  timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    holyGrenade->shoot(direction, angle, power);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}

void Game::shootDynamite(int timeToExplotion)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    dynamite = new Dynamite(&world.world, actualWorm->getXCoordinate(),
                            actualWorm->getYCoordinate(),
                            timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    dynamite->shoot(direction);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}

void Game::teleport(float x, float y)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    actualWorm->getBody()->SetTransform(b2Vec2(x, y), 0);
    actualWorm->getBody()->SetAwake(true);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}

void Game::shootAirStrike(float x, float y)
{
    if (wormAttacked && not endlessTurn)
        return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    if (actualWorm->ammunition[actualWorm->actualWeapon] <= 0 && not infiniteAmmunition) return;
    airStrike.clear();
    for (int i = 0; i < 6; i++)
    {
        airStrike.push_back(new AirStrikeRocket(&world.world, x + 3 * i - 7.5f, y + 40 + 2 * i, config));
    }

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    if (not infiniteAmmunition) {
        actualWorm->ammunition[actualWorm->actualWeapon]--;
    }
}


void Game::throwFragments(float x, float y) {
    Direction direction;
    int j = 0;
    float angleInRadians;
    int angle;
    for (int i = 0; i < 6; i++)
    {
        redGrenadeFragments.push_back(new RedGrenadeFragment(&world.world, x, y, config));
        direction = (i < 3) ? LEFT : RIGHT;
        if (j == 3) {j = 0;}
        angle  = 65 + 15*j;
        angleInRadians = angle * 3.14f / 180.0f;
        redGrenadeFragments[i]->shoot(direction, angleInRadians, 1);
        j++;
    }
}


void Game::executeCommand(std::shared_ptr<Dto> dto)
{
    uint8_t clientId = dto->get_cliente_id();
    if (clientId != idTurn)
        return;
    uint8_t code = dto->return_code();
    if (code == MOVER_A_DERECHA_CODE)
    {
        moveWormRight();
    }
    else if (code == MOVER_A_IZQUIERDA_CODE)
    {
        moveWormLeft();
    }
    else if (code == BATEAR_CODE)
    {
        std::shared_ptr<Batear> batear = std::dynamic_pointer_cast<Batear>(dto);
        int angle = batear->get_angulo();
        batWorm(angle);
    }
    else if (code == SALTAR_CODE)
    {
        std::shared_ptr<Saltar> saltar = std::dynamic_pointer_cast<Saltar>(dto);
        jumpWorm(saltar->get_direccion());
    }
    else if (code == GRANADA_VERDE_CODE)
    {
        std::shared_ptr<GranadaVerde> grenade = std::dynamic_pointer_cast<GranadaVerde>(dto);
        throwGreenGrenade((float)grenade->get_angulo() * 3.14f / 180.0f, grenade->get_potencia(), grenade->get_tiempo());
    }
    else if (code == BAZUKA_CODE)
    {
        std::shared_ptr<Bazuka> bazooka = std::dynamic_pointer_cast<Bazuka>(dto);
        shootBazooka(bazooka->get_angulo() * 3.14f / 180.0f, bazooka->get_potencia());
    }
    else if (code == GRANADA_BANANA_CODE)
    {
        std::shared_ptr<GranadaBanana> granadaBanana = std::dynamic_pointer_cast<GranadaBanana>(dto);
        shootBanana(granadaBanana->get_angulo() * 3.14f / 180.0f, granadaBanana->get_potencia(), granadaBanana->get_tiempo());
    }
    else if (code == GRANADA_SANTA_CODE)
    {
        std::shared_ptr<GranadaSanta> granadaSanta = std::dynamic_pointer_cast<GranadaSanta>(dto);
        shootHolyGrenade(granadaSanta->get_angulo() * 3.14f / 180.0f, granadaSanta->get_potencia(), granadaSanta->get_tiempo());
    }
    else if (code == DINAMITA_CODE)
    {
        std::shared_ptr<Dinamita> dinamita = std::dynamic_pointer_cast<Dinamita>(dto);
        shootDynamite(dinamita->get_tiempo());
    }
    else if (code == TELETRANSPORTAR_CODE)
    {
        std::shared_ptr<Teletransportar> teletransportar = std::dynamic_pointer_cast<Teletransportar>(dto);
        teleport((float)teletransportar->x_pos() / 100.0f, (float)teletransportar->y_pos() / 100.0f);
    }
    else if (code == ATAQUE_AEREO_CODE)
    {
        std::shared_ptr<Misil> misil = std::dynamic_pointer_cast<Misil>(dto);
        shootAirStrike((float)misil->x_pos() / 100.0f, (float)misil->y_pos() / 100.0f);
    }
    else if (code == GRANADA_ROJA_CODE)
    {
        std::shared_ptr<GranadaRoja> grenade = std::dynamic_pointer_cast<GranadaRoja>(dto);
        throwRedGrenade((float)grenade->get_angulo() * 3.14f / 180.0f, grenade->get_potencia(), grenade->get_tiempo());
    }
    else if (code == MORTERO_CODE)
    {
        std::shared_ptr<Mortero> mortero = std::dynamic_pointer_cast<Mortero>(dto);
        shootMortero(mortero->get_angulo() * 3.14f / 180.0f, mortero->get_potencia());
    }
    else if (code == EQUIPAR_ARMA_CODE)
    {   
        if (not hayBombas()) {
            std::shared_ptr<EquiparArma> equiparArma = std::dynamic_pointer_cast<EquiparArma>(dto);
            world.getWormsById()[actualWormId]->equipWeapon(equiparArma->get_arma());
        }
        
    }
    else if (code == CHEAT_CODE) {
        std::shared_ptr<Cheat> cheat = std::dynamic_pointer_cast<Cheat>(dto);
        uint8_t cheat_code = cheat->get_cheat();
        if (cheat_code == VIDA_INFINITA_CODE) {
            if (infiniteHp) {
                infiniteHp = false;
            } else {
                infiniteHp = true;
            }
            for (Worm *worm : world.getWorms()) {
                worm->infiniteHp = infiniteHp;
            }
        } else if (cheat_code == TURNO_INFINITO_CODE) {
            if (endlessTurn) {
                endlessTurn = false;
            } else {
                endlessTurn = true;
            }
        } else if (cheat_code == MUNICION_INFINITA_CODE) {
            if (infiniteAmmunition) {
                infiniteAmmunition = false;
            } else {
                infiniteAmmunition = true;
            }
        }
    }
    
    if (wormAttacked && world.getWormsById()[actualWormId]->getWeapon() != 7 && code != EQUIPAR_ARMA_CODE)
    {
        world.getWormsById()[actualWormId]->equipWeapon(11);
    }
    if (wormAttacked && world.getWormsById()[actualWormId]->getWeapon() == 7 && code != EQUIPAR_ARMA_CODE) {
        world.getWormsById()[actualWormId]->equipWeapon(SIN_ARMA);
    }
    
}
    

bool Game::anyWormMoving()
{
    for (Worm *worm : world.getWorms())
    {
        if (worm->isMoving())
        {
            return true;
        }
    }
    return false;
}

Game::~Game() {}

void Game::broadcast()
{
}
