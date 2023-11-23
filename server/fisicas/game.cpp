#include "game.h"
#include <chrono>
#include <thread>

#define TURN_DURATION 60
#define TIME_LEFT_AFTER_ATTACK 2

std::map<std::string, int> loadConfig(const std::string configFileName) {
    YAML::Node yaml = YAML::LoadFile(configFileName);
    std::map<std::string, int> config;
    config["map"] = yaml["map"].as<int>();
    config["wormHp"] = yaml["worm"]["hp"].as<int>();
    config["wormSpeed"] = yaml["worm"]["speed"].as<int>();
    config["turnDuration"] = yaml["turn_duration"].as<int>();
    config["timeLeftAfterAttack"] = yaml["time_left_after_attack"].as<int>();
    config["dynamiteDamage"] = yaml["dynamite"]["damage"].as<int>();
    config["dynamiteRadius"] = yaml["dynamite"]["radius"].as<int>();
    config["greenGrenadeDamage"] = yaml["green_grenade"]["damage"].as<int>();
    config["greenGrenadeRadius"] = yaml["green_grenade"]["radius"].as<int>();
    config["bazookaDamage"] = yaml["bazooka"]["damage"].as<int>();
    config["bazookaRadius"] = yaml["bazooka"]["radius"].as<int>();
    config["bananaDamage"] = yaml["banana"]["damage"].as<int>();
    config["bananaRadius"] = yaml["banana"]["radius"].as<int>();
    config["holyGrenadeDamage"] = yaml["holy_grenade"]["damage"].as<int>();
    config["holyGrenadeRadius"] = yaml["holy_grenade"]["radius"].as<int>();
    config["airStrikeDamage"] = yaml["air_strike"]["damage"].as<int>();
    config["airStrikeRadius"] = yaml["air_strike"]["radius"].as<int>();
    config["cantidad_de_worms"] = yaml["cantidad_de_worms"].as<int>();
    return config;
}

Game::Game(Queue<std::shared_ptr<Dto>> &queue, Broadcaster &broadcaster) : common_queue(queue),
                                                                           broadcaster(broadcaster),
                                                                           config(loadConfig("/configuracion.yml")),
                                                                           world(World(config)),
                                                                           
                                                                           game_finished(false)
{   
    if (config["map"] == 1) {
        mapa();
    } else if (config["map"] == 2) {
        mapa_jaula();
    } else if(config["map"] == 3) {
        mapa_puente();
    } else {
        mapa_vigas_inclinadas();
    }
}

void Game::mapa() {

    /******************** VIGAS ********************/

    // Piso 0
    int x = 5;
    for (int i = 0; i < 10; i++) {
        world.addBeam(x, 5, 0, LONG);
        x += 6;
    }

    // Piso 1
    x = 5;
    for (int i = 0; i < 10; i++) {

        if (x == 53) {
            x += 6;
            continue;
        }

        world.addBeam(x, 10, 0, LONG);
        x += 6;
    }

    // Piso 2
    x = 5;
    for (int i = 0; i < 10; i++) {

        if (x == 11) {
            x += 6;
            continue;
        }

        world.addBeam(x, 15, 0, LONG);
        x += 6;
    }

    // Piso 3
    x = 5;
    for (int i = 0; i < 10; i++) {

        if (x == 53) {
            x += 6;
            continue;
        }

        world.addBeam(x, 20, 0, LONG);
        x += 6;
    }

    // Piso 4
    x = 5;
    for (int i = 0; i < 10; i++) {

        if (x == 11) {
            x += 6;
            continue;
        }

        world.addBeam(x, 25, 0, LONG);
        x += 6;
    }

    // Techo
    x = 5;
    for (int i = 0; i < 10; i++) {
        world.addBeam(x, 29.7, 0, LONG);
        x += 6;
    }

    // Paredes
    float y = 8.4;
    for (int i = 0; i < 4; i++) {
        world.addBeam(2.4f, y, 90, LONG);
        y += 6;
    }

    y = 8.4;
    for (int i = 0; i < 4; i++) {
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
    for (int i = 0; i < config["cantidad_de_worms"]; i++) {
        world.addWorm(x, 22);
        x += 2;
    }

}

void Game::mapa_jaula() {

    /******************** VIGAS ********************/

    // Piso
    world.addBeam(5, 5, 0, LONG); // 2 3 4 5 6 7 8
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
    for (int i = 0; i < config["cantidad_de_worms"]; i++) {
        world.addWorm(x, 10);
        x += 2;
    }

}

void Game::mapa_puente() {

    /******************** VIGAS ********************/

    world.addBeam(2.4f, 8.4f, 90, LONG);

    world.addBeam(5, 5, 0, LONG); // 2 3 4 5 6 7 8
    world.addBeam(11, 5, 0, LONG); // 8 9 10 11 12 13 14
    world.addBeam(17, 5, 0, LONG); // 14 15 16 17 18 19 20
    world.addBeam(23, 5, 0, LONG); // 20 21 22 23 24 25 26
    world.addBeam(29, 5, 0, LONG);
    world.addBeam(34, 5, 0, LONG);

    world.addBeam(36.6f, 8.4f, 90, LONG);

    /******************** WORMS ********************/

    int x = 3;
    for (int i = 0; i < config["cantidad_de_worms"]; i++) {
        world.addWorm(x, 14);
        x += 2;
    }

}

void Game::mapa_vigas_inclinadas() {

    /******************** VIGAS ********************/

    world.addBeam(3, 9, 0, LONG);
    world.addBeam(11.2f, 10, 0, LONG);
    world.addBeam(18.7f, 11.9f, 0, LONG);

    world.addBeam(7.2f, 9.5f, 22.5f, SHORT);
    world.addBeam(15, 11, 45, SHORT);
    world.addBeam(22, 13.2f, 67.5f, SHORT);

    /******************** WORMS ********************/

    int x = 3;
    for (int i = 0; i < config["cantidad_de_worms"]; i++) {
        world.addWorm(x, 14);
        x += 2;
    }

}

void Game::createPlayers() {
    int numberOfWorms = (int)world.getWorms().size();
    int wormId = 1;
    int teamNumber = 0;
    numberOfPlayers = (int)idPlayers.size();
    idTurn = idPlayers[indexOfActualPlayer];

    for (int playerId : idPlayers) {
        std::vector<int> wormIds;
        for (int i = 0; i < numberOfWorms / numberOfPlayers; i++) {
            wormIds.push_back(wormId);
            world.getWormsById()[wormId]->setPlayerId(playerId);
            world.getWormsById()[wormId]->setTeamNumber(teamNumber);
            wormId++;
        }
        players.push_back(Player(playerId, teamNumber, wormIds));
        teamNumber++;
    }

    actualWormId = players[indexOfActualPlayer].actualWormId;
    numberOfAlivePlayers = numberOfPlayers;
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

            if (dto->is_alive() && dto->return_code() == FINALIZAR_CODE) {
                broadcaster.removeQueueWithId(dto->get_cliente_id()); // elimino la queue del cliente que murio
                broadcaster.notificarCierre(dto);
                broadcaster.deleteAllQueues(); // aviso a los demas que cierren
                stop();
                break;
            }
            // if (not dto->is_alive()) {
            //     stop();
            //     broadcaster.deleteAllQueues();
            // }
            //printf("antes de execute %u\n",dto->return_code());
            executeCommand(dto);
        }
        update();
        limitFrameRate();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
        // broadcast();
    }
}

void Game::addPlayerId(uint8_t id) {
    idPlayers.push_back(id);
}

void Game::passTurn() {
    // cambio de turno 
    end = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() >= config["turnDuration"] ||
        (wormAttacked && std::chrono::duration_cast<std::chrono::seconds> (end - timeOfAttack).count() >= config["timeLeftAfterAttack"])) {
        if (world.anyMovement() || hayBombas())  {
            //std::cout << "hay movimiento\n";
            idTurn = -1;
            return;
        }
        // cuando al gusano se le termina el turno, le saco el arma.
        world.getWormsById()[actualWormId]->equipWeapon(NO_WEAPON);
        updateWorms();
        updatePlayers();
        wormAttacked = false;
        
        
        std::cout << "pasaron " << TURN_DURATION << " segundos, cambio de turno\n";
        std::cout << "turno actual = " << idTurn << "\n";
        
        for (int i = 0; i < numberOfPlayers; i++) {
            if (indexOfActualPlayer == (int)idPlayers.size() - 1) {
                indexOfActualPlayer = 0;
            } else {
                indexOfActualPlayer++;
            }
            if (players[indexOfActualPlayer].isAlive) {
                idTurn = idPlayers[indexOfActualPlayer];
                players[indexOfActualPlayer].changeActualWorm();
                actualWormId = players[indexOfActualPlayer].actualWormId;
                world.getWormsById()[actualWormId]->equipWeapon(NO_WEAPON);
                begin = std::chrono::steady_clock::now();
                return;
            }
        }
        // si no hay jugadores para elegir ==> cierro.
        broadcaster.notificarCierre(std::make_shared<Dto>(FINALIZAR_CODE,1));
        broadcaster.deleteAllQueues(); // aviso a los demas que cierren
        stop();
        return;
        
    }
}

void Game::limitFrameRate() {
    t2 = std::chrono::steady_clock::now();
    rest = (int)rate - std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    if (rest < 0) {
        t1 = t1 - std::chrono::nanoseconds((int)rest); // - rest es positivo
        lost = -rest;
    } else {
        lost = 0;
        std::this_thread::sleep_for(std::chrono::nanoseconds((int)rest));
    }        
    t1 = t1 + std::chrono::nanoseconds((int)rate);
}

void Game::updateWorms() {
    // actualizo los gusanos
    for (Worm *worm : world.getWorms()) {
        //std::cout << "worm x = " << worm->getXCoordinate() << "\n";
        if (not worm->isMoving() && worm->getHp() == 0 && worm->is_alive) {
            worm->is_alive = false;
            begin = std::chrono::steady_clock::now();

            players[worm->playerId - 1].numberOfAliveWorms--;
            players[worm->playerId - 1].markWormAsDead(worm->getId());
            
            
        }
        if (not world.anyMovement()) {
            worm->makeDamage();
            if (worm->getState() == DEAD && actualWormId == worm->getId() && worm->is_alive) {
                players[worm->playerId - 1].markWormAsDead(worm->getId());
                // cambio de turno
                
                for (int i = 0; i < numberOfPlayers; i++) {
                    if (indexOfActualPlayer == (int)idPlayers.size() - 1) {
                        indexOfActualPlayer = 0;
                    } else {
                        indexOfActualPlayer++;
                    }
                    if (players[indexOfActualPlayer].isAlive) {
                        idTurn = idPlayers[indexOfActualPlayer];
                        players[indexOfActualPlayer].changeActualWorm();
                        actualWormId = players[indexOfActualPlayer].actualWormId;
                        world.getWormsById()[actualWormId]->equipWeapon(NO_WEAPON);
                        begin = std::chrono::steady_clock::now();
                        break;
                    }
                }
            }
        }
        if (worm->numberOfContacts == 0) {
            if (worm->getYCoordinate() > worm->highestYCoordinateReached) {
                worm->highestYCoordinateReached = worm->getYCoordinate();
            }
        }
        /*if (worm->getYCoordinate() <= 0) {
            worm->takeDamage(worm->getHp());
        }*/
        if (worm->jumpTimeout > 0) worm->jumpTimeout--;
        if (worm->state == FLYING) {
            worm->updateAngle();
        }
    }
}

void Game::updatePlayers() {
    // actualizo los players
    for (int i = 0; i < numberOfPlayers; i++) {
        
        if (players[i].numberOfAliveWorms == 0 && players[i].isAlive) {
            players[i].isAlive = false;
            numberOfAlivePlayers--;
        }
        if (numberOfAlivePlayers <= 1) {
            uint8_t winnerId;
            for (Player player : players) {
                // el player vivo es el ganador
                if (player.isAlive) {
                    winnerId = player.getId();
                    // notifico el ganador
                    std::shared_ptr<Ganador> ganador = std::make_shared<Ganador>(winnerId);
                    broadcaster.AddDtoToQueues(ganador);
                    break;
                }
            }
            std::cout << "updatePlayers():: No hay jugadores, cierro\n";
            broadcaster.notificarCierre(std::make_shared<Dto>(FINALIZAR_CODE,1));
            broadcaster.deleteAllQueues(); // aviso a los demas que cierren
            stop();
            return;
        }
    }
}

void Game::updateBombs() {
    if (greenGrenade != NULL) {
        greenGrenade->update();
    }
    
    if (bazookaRocket != NULL) {
        if (not bazookaRocket->exploded) {
            bazookaRocket->updateAngle();
        }
    }
    
    if (banana != NULL) {
        banana->update();
    }
    
    if (holyGrenade != NULL) {
        holyGrenade->update();
    }
    
    if (dynamite != NULL) {
        dynamite->update();
    }
    if (redGrenade != NULL) {
        redGrenade->update();
    }
    if (morteroRocket != NULL) {
        if (not morteroRocket->exploded) {
            morteroRocket->updateAngle();
        }
    }
}

void Game::update()
{   
    updateWorms();
    updatePlayers();
    if (game_finished) return;
    updateBombs();
    sendWorms();
    passTurn();
}

bool Game::anyAirStrikeRocket() {
    for (AirStrikeRocket *rocket : airStrike) {
        if (rocket != NULL) {
           
            if (not rocket->exploded) {
                return true;
            }
        }
    }
    std::cout << "no hay mas cohetes del ataque aereo\n";
    return false;
}

bool Game::hayBombas() {
    if (greenGrenade != NULL || banana != NULL || dynamite != NULL || 
        bazookaRocket != NULL || holyGrenade != NULL || redGrenade != NULL || morteroRocket != NULL) {
        return true;
    }
    for (AirStrikeRocket *rocket : airStrike) {
        if (rocket != NULL) {
            return true;
        }
    }
    for (RedGrenadeFragment *fragment : redGrenadeFragments) {
        if (fragment != NULL) {
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
        if (w->is_alive) {
            //std::cout << "sendWorms(), w->getHp() = " << (int)w->getHp() << "\n";
            std::shared_ptr<Gusano> g = std::make_shared<Gusano>((w->getId()),
                                                    (int)(w->getXCoordinate() * 100),
                                                    (int)(w->getYCoordinate() * 100),
                                                    w->getHp(),
                                                    w->getTeamNumber(),
                                                    w->getState(),
                                                    w->getWeapon(),
                                                    w->getDirection(),
                                                    (uint8_t)w->getAngle()
                                                    );
            vectorGusanos.push_back(g);
        }
        
        

        // IF NO ESTA VIVO Y ESTA QUIETO O COLISIONANDO CONTRA LA VIGA -> LO ELIMINAS

    }
    std::shared_ptr<Gusanos> gusanos = std::make_shared<Gusanos>(vectorGusanos);

    int id = players[indexOfActualPlayer].getActualWormId(); // obtengo el id del gusano actual
    //int id = 1;
    gusanos->set_gusano_de_turno(id);

    // SI HAY GRANADA
    std::vector<std::shared_ptr<Proyectil>> proyectiles ;
    if (hayBombas()) {
        gusanos->set_flag_proyectil(true);
    }

    broadcaster.AddDtoToQueues(gusanos);
    // crear granada
    if (hayBombas()) {
        if (greenGrenade != NULL) {
            std::shared_ptr<GranadaVerde> granada = std::make_shared<GranadaVerde>((uint16_t)(greenGrenade->getXCoordinate() * 100), (uint16_t)(greenGrenade->getYCoordinate() * 100), (uint8_t)(greenGrenade->getAngle()), greenGrenade->exploded);
            proyectiles.push_back(granada);

            if (greenGrenade->exploded) {
                greenGrenade->destroy();
                greenGrenade = NULL;
            }
        }

        if (redGrenade != NULL) {
            std::shared_ptr<GranadaRoja> granadaRoja = std::make_shared<GranadaRoja>((uint16_t)(redGrenade->getXCoordinate() * 100), (uint16_t)(redGrenade->getYCoordinate() * 100), (uint8_t)(redGrenade->getAngle()), redGrenade->exploded);
            proyectiles.push_back(granadaRoja);

            if (redGrenade->exploded) {
                
                float x = redGrenade->getXCoordinate();
                float y = redGrenade->getYCoordinate() + 1;
                Direction direction;
                int j = 0;
                for (int i = 0; i < 6; i++) {
                    redGrenadeFragments.push_back(new RedGrenadeFragment(&world.world, x, y, config));
                    direction = (i < 3) ? LEFT : RIGHT;
                    if (i == 3) {j = 0;}
                    float angle = (float)(9.0f*j + 70.0f);
                    redGrenadeFragments[i]->shoot(direction, angle, 2);
                    j++;
                }
                redGrenade->destroy();
                redGrenade = NULL;
                // falta enviar los fragmentos
            }
        }
        
        if (bazookaRocket != NULL) {
            std::shared_ptr<Bazuka> bazooka = std::make_shared<Bazuka>((uint16_t)(bazookaRocket->getXCoordinate() * 100), (uint16_t)(bazookaRocket->getYCoordinate() * 100), (uint16_t)(bazookaRocket->getAngle()), bazookaRocket->dir, bazookaRocket->exploded);

            proyectiles.push_back(bazooka);
            if (bazookaRocket->exploded) {
                bazookaRocket->destroy();
                bazookaRocket = NULL;
            }
        }
        
        if (banana != NULL) {
            std::shared_ptr<GranadaBanana> granadaBanana = std::make_shared<GranadaBanana>((uint16_t)(banana->getXCoordinate() * 100), (uint16_t)(banana->getYCoordinate() * 100), (uint8_t)(banana->getAngle()), banana->exploded);
            proyectiles.push_back(granadaBanana);
            if (banana->exploded) {
                banana->destroy();
                banana = NULL;
            }
        }
        
        if (holyGrenade != NULL) {
            std::shared_ptr<GranadaSanta> granadaSanta = std::make_shared<GranadaSanta>((uint16_t)(holyGrenade->getXCoordinate() * 100), (uint16_t)(holyGrenade->getYCoordinate() * 100), (uint8_t)holyGrenade->getAngle(), holyGrenade->exploded);
            proyectiles.push_back(granadaSanta);
            if (holyGrenade->exploded) {
                holyGrenade->destroy();
                holyGrenade = NULL;
            }
        }
        
        if (dynamite != NULL) {
            std::shared_ptr<Dinamita> dinamita = std::make_shared<Dinamita>((uint16_t)(dynamite->getXCoordinate() * 100), (uint16_t)(dynamite->getYCoordinate() * 100), dynamite->exploded);
            
            proyectiles.push_back(dinamita);
            if (dynamite->exploded) {
                dynamite->destroy();
                dynamite = NULL;
            }
        }
        
        if (morteroRocket != NULL) {
            std::shared_ptr<Mortero> mortero = std::make_shared<Mortero>((uint16_t)(morteroRocket->getXCoordinate() * 100), (uint16_t)(morteroRocket->getYCoordinate() * 100), (uint16_t)(morteroRocket->getAngle()), morteroRocket->dir, morteroRocket->exploded);
            proyectiles.push_back(mortero);
            if (morteroRocket->exploded) {
                float x = morteroRocket->getXCoordinate();
                float y = morteroRocket->getYCoordinate();
                Direction direction;
                int j = 0;
                for (int i = 0; i < 6; i++) {
                    redGrenadeFragments.push_back(new RedGrenadeFragment(&world.world, x, y, config));
                    direction = (i < 3) ? LEFT : RIGHT;
                    if (i == 3) {j = 0;}
                    redGrenadeFragments[i]->shoot(direction, 10*j + 60, 1);
                }
                morteroRocket->destroy();
                morteroRocket = NULL;
            }
        }

        
        int id_proyectil = 1;
        for (int i = 0; i < (int)airStrike.size(); i++) {
            if (airStrike[i] != NULL) {
                std::shared_ptr<Misil> misil = std::make_shared<Misil>(id_proyectil, (uint16_t)(airStrike[i]->getXCoordinate() * 100), (uint16_t)(airStrike[i]->getYCoordinate() * 100), airStrike[i]->exploded);
                proyectiles.push_back(misil);
                if (airStrike[i]->exploded) {
                    //delete rocket;
                    airStrike[i]->destroy();
                    airStrike[i] = NULL;
                }
            }
            id_proyectil++;
        }
        
        int id_fragmento = 1;
        for (int i = 0; i < (int)redGrenadeFragments.size(); i++) {
            if (redGrenadeFragments[i] != NULL) {
                //std::cout << "enviando fragmento " << id_fragmento << "\n";
                std::shared_ptr<Fragmento> fragmento = std::make_shared<Fragmento>(id_fragmento, (uint16_t)(redGrenadeFragments[i]->getXCoordinate() * 100), (uint16_t)(redGrenadeFragments[i]->getYCoordinate() * 100), 0, redGrenadeFragments[i]->exploded);
                proyectiles.push_back(fragmento);
                if (redGrenadeFragments[i]->exploded) {
                    //std::cout << "----------------fragmento " << id_fragmento << " exploto\n";
                    //redGrenadeFragments[i]->destroy();
                    explodedFragmentIds.push_back(i);
                    redGrenadeFragments[i]->destroy();
                    redGrenadeFragments[i] = NULL;
                }
                
            }
            id_fragmento++;
        }

        if (proyectiles.size() > 0) {
            std::shared_ptr<Proyectiles> ps = std::make_shared<Proyectiles>(proyectiles);    
            broadcaster.AddDtoToQueues(ps);
        }
    } 
}

void Game::sendMap()
{
    std::vector<std::shared_ptr<Viga>> vs;
    // por cada viga manda un Dto Viga a los senders
    for (auto &beam : world.getBeams())
    {
        // cambiar los parametros a float
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

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    // lista de gusano = diccionario [ID];

    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->moveRight();
    // std::cout << "posicion gusano = " << world.getWorms().front()->getXCoordinate() << "\n";
}

void Game::moveWormLeft()
{

    // ACCEDEMOS A LA LISTA DE SUS GUSANOS USANDO SU ID EN EL DICCIONARIO

    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->moveLeft();
}

void Game::jumpWorm(uint8_t direction) {
    // direction = 0 ==> forward
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    if (direction == 0) {
        world.getWormsById()[idActualWorm]->jump();
    } else {
        world.getWormsById()[idActualWorm]->jumpBackward();
    }
}

void Game::batWorm(int angle) {
    if (wormAttacked) return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    world.getWormsById()[idActualWorm]->bat(world.getWorms(), angle);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::stop()
{
    game_finished = true;
    // liberar memoria
}

void Game::throwGreenGrenade(float angle, int power, int timeToExplotion) {
    if (wormAttacked) return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    greenGrenade = new GreenGrenade(&world.world, actualWorm->getXCoordinate(), 
                                    actualWorm->getYCoordinate(),
                                    timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    greenGrenade->shoot(direction, angle, power);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
    //actualWorm->equipWeapon(NO_WEAPON);
}

void Game::throwRedGrenade(float angle, int power, int timeToExplotion) {
    if (wormAttacked) return;

    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    redGrenade = new RedGrenade(&world.world, actualWorm->getXCoordinate(), 
                                    actualWorm->getYCoordinate(),
                                    timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    redGrenade->shoot(direction, angle, power);
    redGrenadeFragments.clear();
    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}



void Game::shootBazooka(float angle, int power) {
    if (wormAttacked) return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    bazookaRocket = new BazookaRocket(&world.world, actualWorm->getXCoordinate(), 
                                    actualWorm->getYCoordinate(), angle, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    bazookaRocket->shoot(direction, angle, power);
    
    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::shootMortero(float angle, int power) {
    if (wormAttacked) return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    morteroRocket = new MorteroRocket(&world.world, actualWorm->getXCoordinate(), 
                                    actualWorm->getYCoordinate(), angle, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    morteroRocket->shoot(direction, angle, power);
    redGrenadeFragments.clear();
    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::shootBanana(float angle, int power, int timeToExplotion) {
    if (wormAttacked) return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    banana = new Banana(&world.world, actualWorm->getXCoordinate(), 
                                    actualWorm->getYCoordinate(),
                                    timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    banana->shoot(direction, angle, power);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::shootHolyGrenade(float angle, int power, int timeToExplotion) {
    if (wormAttacked) return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    holyGrenade = new HolyGrenade(&world.world, actualWorm->getXCoordinate(), 
                                    actualWorm->getYCoordinate(),
                                    timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    holyGrenade->shoot(direction, angle, power);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::shootDynamite(int timeToExplotion) {
    if (wormAttacked) return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    dynamite = new Dynamite(&world.world, actualWorm->getXCoordinate(), 
                                    actualWorm->getYCoordinate(),
                                    timeToExplotion, config);
    Direction direction = (actualWorm->facingRight) ? RIGHT : LEFT;
    dynamite->shoot(direction);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}


void Game::teleport(float x, float y) {
    if (wormAttacked) return;
    int idActualWorm = players[indexOfActualPlayer].getActualWormId();
    Worm *actualWorm = world.getWormsById()[idActualWorm];
    actualWorm->getBody()->SetTransform(b2Vec2(x, y), 0);
    actualWorm->getBody()->SetAwake(true);

    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}

void Game::shootAirStrike(float x, float y) {
    if (wormAttacked) return;
    //airStrikeRocket = new AirStrikeRocket(&world.world, x, y);
    airStrike.clear();
    for (int i = 0; i < 6; i++) {
        std::cout<<"cohete +1\n";
        airStrike.push_back(new AirStrikeRocket(&world.world, x + 3*i - 7.5f, y + 40 + 2*i, config));
        //airStrike[i]->shoot();
    }
    
    timeOfAttack = std::chrono::steady_clock::now();
    wormAttacked = true;
}


void Game::executeCommand(std::shared_ptr<Dto> dto)
{
    uint8_t clientId = dto->get_cliente_id();
    //std::cout << "clientId = " << (int)clientId << "\n";
    if (clientId != idTurn) return;
    uint8_t code = dto->return_code();
    //printf("codigo mate %u\n",code);
    if (code == MOVER_A_DERECHA_CODE)
    {
        moveWormRight(); // SI ES SU TURNO, LE PASAMOS EL ID
    }
    else if (code == MOVER_A_IZQUIERDA_CODE)
    {
        moveWormLeft(); // SI ES SU TURNO, LE PASAMOS EL ID
    }
    else if (code == BATEAR_CODE) {
        std::shared_ptr<Batear> batear = std::dynamic_pointer_cast<Batear>(dto);
        int angle = batear->get_angulo();
        batWorm(angle);
    } else if (code == SALTAR_CODE) {
        std::shared_ptr<Saltar> saltar = std::dynamic_pointer_cast<Saltar>(dto);
        jumpWorm(saltar->get_direccion());
    }
    else if (code == GRANADA_VERDE_CODE) {
        std::shared_ptr<GranadaVerde> grenade = std::dynamic_pointer_cast<GranadaVerde>(dto);
        throwGreenGrenade((float)grenade->get_angulo() * 3.14f / 180.0f, grenade->get_potencia(), grenade->get_tiempo());
    } else if (code == BAZUKA_CODE) {
        std::shared_ptr<Bazuka> bazooka = std::dynamic_pointer_cast<Bazuka>(dto);
        shootBazooka(bazooka->get_angulo() * 3.14f / 180.0f, bazooka->get_potencia());
    } else if (code == GRANADA_BANANA_CODE) {
        std::shared_ptr<GranadaBanana> granadaBanana = std::dynamic_pointer_cast<GranadaBanana>(dto);
        shootBanana(granadaBanana->get_angulo() * 3.14f / 180.0f, granadaBanana->get_potencia(), granadaBanana->get_tiempo());
    } else if (code == GRANADA_SANTA_CODE) {
        std::shared_ptr<GranadaSanta> granadaSanta = std::dynamic_pointer_cast<GranadaSanta>(dto);
        shootHolyGrenade(granadaSanta->get_angulo() * 3.14f / 180.0f, granadaSanta->get_potencia(), granadaSanta->get_tiempo());
    } else if (code == DINAMITA_CODE) {
        std::shared_ptr<Dinamita> dinamita = std::dynamic_pointer_cast<Dinamita>(dto);
        shootDynamite(dinamita->get_tiempo());
    }
    else if (code == TELETRANSPORTAR_CODE) {
        std::shared_ptr<Teletransportar> teletransportar = std::dynamic_pointer_cast<Teletransportar>(dto);
        teleport((float)teletransportar->x_pos() / 100.0f, (float) teletransportar->y_pos() / 100.0f);
    }
    else if (code == ATAQUE_AEREO_CODE) {
        std::shared_ptr<Misil> misil = std::dynamic_pointer_cast<Misil>(dto);
        std::cout << "game-> ataque aereo x = " << (int)misil->x_pos() << ", y = " << (int)misil->y_pos() << "\n";
        shootAirStrike((float)misil->x_pos() / 100.0f, (float) misil->y_pos() / 100.0f);
    }
    else if (code == GRANADA_ROJA_CODE) {
        std::cout << "game->granada roja\n";
        std::shared_ptr<GranadaRoja> grenade = std::dynamic_pointer_cast<GranadaRoja>(dto);
        throwRedGrenade((float)grenade->get_angulo() * 3.14f / 180.0f, grenade->get_potencia(), grenade->get_tiempo());
    }
    else if (code == MORTERO_CODE) {
        std::shared_ptr<Mortero> mortero = std::dynamic_pointer_cast<Mortero>(dto);
        shootMortero(mortero->get_angulo() * 3.14f / 180.0f, mortero->get_potencia());
    }
    else if (code == EQUIPAR_ARMA_CODE) {
        std::shared_ptr<EquiparArma> equiparArma = std::dynamic_pointer_cast<EquiparArma>(dto);
        world.getWormsById()[actualWormId]->equipWeapon(equiparArma->get_arma());
    }

    if (wormAttacked) {
        world.getWormsById()[actualWormId]->equipWeapon(NO_WEAPON);
    }
}

bool Game::anyWormMoving() {
    for (Worm *worm : world.getWorms()) {
        if (worm->isMoving()) {
            return true;
        }
    }
    return false;
}

Game::~Game() {}

void Game::broadcast()
{
}
