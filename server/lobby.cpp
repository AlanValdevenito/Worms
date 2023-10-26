#include "lobby.h"

Lobby::Lobby() : game(common_queue, broadcaster)
{
    game.start();
}

Lobby::~Lobby() {}

void Lobby::newClient(Socket &&s)
{
    ServerClient *c = new ServerClient(std::move(s), std::ref(broadcaster), std::ref(common_queue));
    c->start();

    reap_dead();

    clients.push_back(c);

    broadcaster.addQueueToList(c->sender_queue); // agrego la cola send al broadcaster

    // aca se deberia pedir la partida

    // mandar_mapa
    // c->addMapToQueue();
    game.broadcast(c->sender_queue); // le mando el mapa a la cola sender
}

void Lobby::reap_dead()
{
    bool was_removed = false;
    std::list<BlockingQueue *> client_queues;

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
        for (BlockingQueue *q : client_queues)
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
    game.game_finished = true;
}
