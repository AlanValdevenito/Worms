#include "lobby.h"

// crear una nueva instancia de game cuando creo una partida y pasarselo a la partida
// Lobby::Lobby() : mapId(0)
Lobby::Lobby() : mapId(0), partida(std::ref(common_queue), 1, 2), id_cliente(0)
{
    // partida.start();
}

Lobby::~Lobby() {}

// void Lobby::sendMatchList(ServerClient *c)
// {

//     // if (partidas.size() == 0)
//     // {
//     //     Partida p(std::ref(common_queue));
//     //     p.start(c);
//     //     partidas.push_back(p);
//     // }
//     Partida *p1 = new Partida(std::ref(common_queue), 1);
//     Partida *p2 = new Partida(std::ref(common_queue), 2);
//     partidas.push_back(p1);
//     partidas.push_back(p2);

//     ListaDePartidas *l = new ListaDePartidas();
//     l->addOption(p1->getId());
//     l->addOption(p2->getId());

//     c->sender_queue.push(l); // le envio la lista al cliente

//     ListaDePartidas *partida = (ListaDePartidas *)lobby_queue.pop(); // recibo la rta

//     if (partida->seleccionada == 1)
//     {
//         std::cout << "Entro a la partida 1\n";
//         p1->start(c);
//     }
//     else if (partida->seleccionada == 2)
//     {

//         std::cout << "Entro a la partida 2\n";
//         p2->start(c);
//     }
//     else
//         std::cout << "ninguna partida seleccionada\n";
// }

void Lobby::newClient(Socket &&s)
{
    id_cliente++;

    // agregar lobby queue
    ServerClient *c = new ServerClient(std::move(s), std::ref(lobby_queue), std::ref(common_queue), id_cliente); // no necesita el broadcaster
    c->start();

    reap_dead();

    clients.push_back(c);
    // sendMatchList(c);

    // me parece que va a ser de cada partida
    // broadcaster.addQueueToList(c->sender_queue); // agrego la cola send al broadcaster

    // aca se deberia pedir la partida
    // send y recv lista de partidas
    // enviar_lista_de_partidas(c->sender_queue);

    // send y recv lista de mapas ----------------> SOLO PARA PARTIDAS NUEVAS????
    // Partida p(std::ref(common_queue));
    partida.sendMapTo(c);
    partida.start();
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

    // if (was_removed)
    // {
    //     for (Queue<Dto *> *q : client_queues)
    //         broadcaster.removeQueueFromList(q);
    // }
}

void Lobby::kill()
{
    for (auto &c : clients)
    {
        c->kill();
        c->join();
        delete c;
    }
    // broadcaster.deleteAllQueues();
    clients.clear();

    // game.game_finished = true;
    // for (Partida *p : partidas)
    // {
    //     p->finish();
    //     delete p;
    // }
    partida.finish();
}
