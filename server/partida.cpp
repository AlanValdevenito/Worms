#include "partida.h"

Partida::Partida(Queue<std::shared_ptr<Dto>> &cq, uint8_t id, int cant) : common_queue(cq), game(cq, broadcaster), id(id), jugadores(cant), conectados(0) {}
Partida::~Partida() {}

void Partida::start()
{
    // std::cout<<"cantidad de jugadores: "<<jugadores<<std::endl;
    // std::cout<<"cantidad de conectados: "<<conectados<<std::endl;
    if (jugadores > conectados)
        return;

    broadcaster.addMessageToQueues();

    game.sendMap(); // le mando el mapa a la cola sender
    game.sendWorms();

    game.start();
}

void Partida::sendMapTo(ServerClient *c)
{
    if (conectados == jugadores)
        return;

    conectados++;
    broadcaster.addQueueToList(c->sender_queue, c->id); // agrego la cola send al broadcaster
}

void Partida::finish() 
{ 
    game.stop(); 
    broadcaster.deleteAllQueues();
}

bool Partida::is_dead() { return game.game_finished; }

void Partida::join() 
{
    // std::cout << "sale de la partida\n";
    broadcaster.deleteAllQueues();
    game.join(); 
}

uint8_t Partida::getId() { return id; }
