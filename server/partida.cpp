#include "partida.h"

Partida::Partida(Queue<Dto *> &cq, uint8_t id) : common_queue(cq), game(cq, broadcaster), id(id) { game.start(); }
Partida::~Partida() {}

void Partida::start(ServerClient *c)
{
    broadcaster.addQueueToList(c->sender_queue); // agrego la cola send al broadcaster

    game.sendMap(c->sender_queue); // le mando el mapa a la cola sender // CAMBIAAARS

    game.sendWorms(c->sender_queue);
}

void Partida::finish() { game.game_finished = true; }

uint8_t Partida::getId() { return id; }
