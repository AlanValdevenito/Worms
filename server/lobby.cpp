#include "lobby.h"

// crear una nueva instancia de game cuando creo una partida y pasarselo a la partida
Lobby::Lobby() : mapId(0), id_cliente(0)
{
    Partida *p1 = new Partida(1, 2);
    Partida *p2 = new Partida(2, 1);
    partidas.push_back(p1);
    partidas.push_back(p2);
}

Lobby::~Lobby() {}

void Lobby::sendMatchList(ServerClient *c)
{

    // if (partidas.size() == 0)
    // {
    //     Partida p(std::ref(common_queue));
    //     p.start(c);
    //     partidas.push_back(p);
    // }

    Partida *p1 = partidas.front();
    Partida *p2 = partidas.back();

    std::shared_ptr<ListaDePartidas> l = std::make_shared<ListaDePartidas>();
    l->addOption(p1->getId());
    l->addOption(p2->getId());

    c->sender_queue.push(l); // le envio la lista al cliente

    std::shared_ptr<ListaDePartidas> partida = std::dynamic_pointer_cast<ListaDePartidas>(lobby_queue.pop()); // recibo la rta

    if (partida->seleccionada == 1)
    {
        std::cout << "Entro a la partida 1\n";
        p1->sendMapTo(c);
        p1->start();
    }
    else if (partida->seleccionada == 2)
    {

        std::cout << "Entro a la partida 2\n";
        p2->sendMapTo(c);
        p2->start();
    }
    else
        std::cout << "ninguna partida seleccionada\n";
}

void Lobby::newClient(Socket &&s)
{
    id_cliente++;

    ServerClient *c = new ServerClient(std::move(s), &lobby_queue, id_cliente);
    c->start();

    // reap_dead();
    
    sendMatchList(c);
}

void Lobby::removerPartidasMuertas()
{
    partidas.remove_if([&](Partida *p)
                       {
            if (p->is_dead()) {
                p->finish(); // hace falta?
                p->join();
                delete p;
                return true;
            }
            return false; });
}

void Lobby::reap_dead() {removerPartidasMuertas();}

void Lobby::kill()
{
    for (Partida *p : partidas)
    {
        p->forceFinish();
        std::cout << "sale del force\n";
        delete p;
        std::cout << "delete\n";
    }

    partidas.clear();
}
