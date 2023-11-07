#include "partida.h"
#include<unistd.h>

Partida::Partida(uint8_t id, int cant) : game(common_queue, broadcaster), id(id), jugadores(cant), conectados(0), partida_empezada(false) {}
Partida::~Partida() {}

void Partida::start()
{
    if (jugadores > conectados)
        return;

    //emepzo la partida
    partida_empezada = true;    

    for(ServerClient* c : clients)
        game.addPlayerId(c->id);

    game.createPlayers();
    
    broadcaster.addMessageToQueues(); // agrega mensaje de inicio de partida

    game.sendMap(); // le mando el mapa a la cola sender
    game.sendWorms();

    game.start();
}

void Partida::sendMapTo(ServerClient *c)
{
    if (conectados == jugadores)
        return;

    conectados++;
    c->changeReceiverQueue(&common_queue);

    clients.push_back(c);
    broadcaster.addQueueToList(c->sender_queue, c->id); // agrego la cola send al broadcaster
}

void Partida::forceFinish(){

    if(partida_empezada){
        game.stop();    
        game.join();    
        
        std::shared_ptr<Dto> fin = std::make_shared<Dto>(FINALIZAR_CODE);
        broadcaster.notificarCierre(fin);

        sleep(5); // Consultar si esta bien
        
        broadcaster.deleteAllQueues();
    }

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

void Partida::join()
{
    broadcaster.deleteAllQueues();
    game.join();
}

uint8_t Partida::getId() { return id; }
