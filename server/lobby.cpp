#include "lobby.h"

// crear una nueva instancia de game cuando creo una partida y pasarselo a la partida
Lobby::Lobby() : mapId(0), partida(std::ref(common_queue))
{
    // partida.start();
}

Lobby::~Lobby() {}

// void Lobby::partida(Game &game, ServerClient *c)
// {
//     // partida le va a pasar el mapa  y se lo guarda

//     // mandar_mapa
//     // c->addMapToQueue();
//     game.sendMap(c->sender_queue); // le mando el mapa a la cola sender // CAMBIAAARS

//     game.sendWorms(c->sender_queue);
// }

void Lobby::newClient(Socket &&s)
{
    ServerClient *c = new ServerClient(std::move(s), std::ref(broadcaster), std::ref(common_queue)); // no necesita el broadcaster
    c->start();

    reap_dead();

    clients.push_back(c);
    // sendMatchList();

    // me parece que va a ser de cada partida
    // broadcaster.addQueueToList(c->sender_queue); // agrego la cola send al broadcaster

    // aca se deberia pedir la partida
    // send y recv lista de partidas
    // enviar_lista_de_partidas(c->sender_queue);

    // send y recv lista de mapas ----------------> SOLO PARA PARTIDAS NUEVAS????
    // Partida p(std::ref(common_queue)); // NO PASARLE EL BROADCASTER
    partida.start(c);
}

void Lobby::reap_dead()
{
    bool was_removed = false;
    std::list<Queue<Dto *> *> client_queues;

    clients.remove_if([&](ServerClient *c)
                      {
            if (c->is_dead()) {
                c->join();
                was_removed = true;
                client_queues.push_back(&c->sender_queue);  // obtengo el puntero de la queue para eliminarlo despues
                delete c;
                return true;
            }
            return false; });

    if (was_removed)
    {
        for (Queue<Dto *> *q : client_queues)
            broadcaster.removeQueueFromList(q);
    }
}

void Lobby::kill()
{
    for (auto &c : clients)
    {
        c->kill();
        c->join();
        delete c;
    }
    broadcaster.deleteAllQueues();
    clients.clear();

    // game.game_finished = true;
    partida.finish();
    // paridas.finish();
}
