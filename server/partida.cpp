#include "partida.h"

Partida::Partida(Queue<std::shared_ptr<Dto>> &cq, uint8_t id, int cant) : common_queue(cq), game(cq, broadcaster), id(id), jugadores(cant), conectados(0) {} // game.start(); }
Partida::~Partida() {}

void Partida::start()
{
    std::cout<<"cantidad de jugadores: "<<jugadores<<std::endl;
    std::cout<<"cantidad de conectados: "<<conectados<<std::endl;
    if (jugadores > conectados)
        return;

    std::cout << "primero mando msj \n";
    broadcaster.addMessageToQueues();

    std::cout << "empieza la partida \n";

    game.sendMap(); // le mando el mapa a la cola sender
    game.sendWorms();

    game.start();
}

void Partida::sendMapTo(ServerClient *c)
{
    if (conectados == jugadores)
        return;

    conectados++;
    broadcaster.addQueueToList(c->sender_queue); // agrego la cola send al broadcaster
}

void Partida::finish() { game.game_finished = true; }

uint8_t Partida::getId() { return id; }
