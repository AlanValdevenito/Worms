#include "partida.h"

Partida::Partida(Queue<Dto *> &cq, uint8_t id, int cant) : common_queue(cq), game(cq, broadcaster), id(id), jugadores(cant), conectados(0) {} //game.start(); }
Partida::~Partida() {}

void Partida::start(){
    if(jugadores > conectados) return;

    game.sendWorms();

    game.start();
}

void Partida::sendMapTo(ServerClient *c)
{
    if(conectados == jugadores) return;

    conectados++;
    broadcaster.addQueueToList(c->sender_queue); // agrego la cola send al broadcaster

    game.sendMap(c->sender_queue); // le mando el mapa a la cola sender // CAMBIAAARS

}

void Partida::finish() { game.game_finished = true; }

uint8_t Partida::getId() { return id; }
