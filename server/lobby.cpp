#include "lobby.h"

// crear una nueva instancia de game cuando creo una partida y pasarselo a la partida
Lobby::Lobby() : mapId(0), id_cliente(0), partida_id(1)
{
    Partida *p1 = new Partida(partida_id, 2);
    partidas.push_back(p1);
    partida_id++;
}

Lobby::~Lobby() {}

void Lobby::agregarClienteAPartida(ServerClient *c, std::shared_ptr<ListaDePartidas> partida)
{

    for (Partida *p : partidas)
    {
        if (p->getId() == partida->seleccionada)
        {
            printf("CLIENTE AGREGADO A PARTIDA: %u\n", p->getId());
            p->sendMapTo(c);
            p->start();
        }
    }
}

void Lobby::sendMatchList(ServerClient *c)
{

    std::shared_ptr<ListaDePartidas> partidas_disponibles = std::make_shared<ListaDePartidas>();
    for (Partida *p : partidas)
    {
        if(not p->esta_completa()) {// si no esta completa es porque se puede unir
            partidas_disponibles->addOption(p->getId());
            printf("id disponible: %u\n", p->getId());
        }
    }

    c->sender_queue.push(partidas_disponibles); // le envio la lista al cliente

    std::shared_ptr<Dto> respuesta = lobby_queue.pop(); // recibo la rta

    if (respuesta->return_code() == LISTA_DE_PARTIDAS_CODE)
    {
        std::shared_ptr<ListaDePartidas> partida = std::dynamic_pointer_cast<ListaDePartidas>(respuesta);
        printf("PARTIDA SELECCIONADA: %u\n", partida->seleccionada);
        agregarClienteAPartida(c, partida);
    }
    else
    {
        std::shared_ptr<NuevaPartida> nueva_partida = std::dynamic_pointer_cast<NuevaPartida>(respuesta);
        // printf("Nueva Partida con cant de jugadores: %u\n", nueva_partida->get_cantidad_de_jugadores());
        Partida *p = new Partida(partida_id, nueva_partida->get_cantidad_de_jugadores());
        partidas.push_back(p);
        p->sendMapTo(c);
        p->start();
        partida_id++;
    }
}

void Lobby::newClient(Socket *s)
{
    id_cliente++;

    ServerClient *c = new ServerClient(s, &lobby_queue, id_cliente);
    c->start();

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

void Lobby::reap_dead() { removerPartidasMuertas(); }

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
