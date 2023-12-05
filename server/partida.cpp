#include "partida.h"
#include <unistd.h>

Partida::Partida(uint8_t id, int cant, uint8_t mapa) : game(common_queue, broadcaster, cant, mapa), id(id), jugadores(cant), conectados(0), partida_empezada(false) {}
Partida::~Partida() {}

void Partida::tryToStart()
{
    if (jugadores > conectados) // si hay igual cantidad de conectados que de esperados, empieza
        return;

    // emepzo la partida
    partida_empezada = true;

    for (ServerClient *c : clients)
        game.addPlayerId(c->id);

    game.createPlayers();

    broadcaster.addMessageToQueues(); // agrega mensaje de inicio de partida

    game.sendMap(); // le mando el mapa a la cola sender
    game.sendWorms();

    game.start();
}

void Partida::addToMatch(ServerClient *c)
{
    if (conectados == jugadores)
        return;

    conectados++;
    c->changeReceiverQueue(&common_queue);

    clients.push_back(c);
    broadcaster.addQueueToList(c->sender_queue, c->id); // agrego la cola send al broadcaster
}

void Partida::forceFinish()
{

    if (partida_empezada)
    {
        game.stop();
        game.join();
    }
    broadcaster.notificarCierre();
    sleep(1);
    broadcaster.deleteAllQueues();

    for (auto &c : clients)
    {
        c->kill();
        c->join();
        delete c;
    }
    clients.clear();
}

void Partida::finish()
{
    game.stop();
    broadcaster.deleteAllQueues();

    clients.remove_if([&](ServerClient *c)
                      {
            if (c->is_dead()) {
                c->join();
                delete c;
                return true;
            }
            return false; });
}

bool Partida::is_dead() { return game.game_finished; }

bool Partida::esta_completa() { return partida_empezada; }

void Partida::join()
{
    broadcaster.deleteAllQueues();
    game.join();
}

uint8_t Partida::getId() { return id; }
