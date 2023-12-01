#include "lobby.h"

// Hay una partida creada por default para facilitar las pruebas
Lobby::Lobby() : mapId(0), id_cliente(0), partida_id(1), lobby_abierto(true)
{
    Partida *p1 = new Partida(partida_id, 2,1);
    partidas.push_back(p1);
    partida_id++;
}

Lobby::~Lobby() {}

// void Lobby::agregarClienteAPartida(ServerClient *c, std::shared_ptr<ListaDePartidas> partida)
void Lobby::agregarClienteAPartida(ServerClient *c, std::shared_ptr<Dto> lista)
{
    std::shared_ptr<ListaDePartidas> partida = std::dynamic_pointer_cast<ListaDePartidas>(lista);

    for (Partida *p : partidas)
    {
        if (p->getId() == partida->seleccionada)
        {
            // printf("CLIENTE AGREGADO A PARTIDA: %u\n", p->getId());
            p->addToMatch(c);
            p->tryToStart();
        }
    }
}

void Lobby::crearNuevaPartida(ServerClient *c, std::shared_ptr<Dto> np)
{
    std::shared_ptr<NuevaPartida> nueva_partida = std::dynamic_pointer_cast<NuevaPartida>(np);

    Partida *p = new Partida(partida_id, nueva_partida->get_cantidad_de_jugadores(), nueva_partida->get_mapa());
    
    partidas.push_back(p);
    
    // agrego al cliente a la partida
    p->addToMatch(c); // cambiar a addToPartida
    p->tryToStart(); // si esta completa comienza ( no va a estarlo porque es nueva)
    partida_id++;
}

void Lobby::sendMatchList(ServerClient *c)
{
    std::shared_ptr<ListaDePartidas> partidas_disponibles = std::make_shared<ListaDePartidas>();
    for (Partida *p : partidas)
    {
        if (not p->esta_completa()) // si no esta completa es porque se puede unir
            partidas_disponibles->addOption(p->getId());
        // printf("id disponible: %u\n", p->getId());
    }
    c->sender_queue.push(partidas_disponibles); // le envio la lista al cliente
}

void Lobby::addToPartida(ServerClient *c){
    
    sendMatchList(c);

    int contador = 0;
    std::shared_ptr<Dto> respuesta = NULL;

    // si el contador llega a la espera maxima se cierra el cliente
    // esto es para si el jugador tarda mucho, se lo eche y se deje entrar a otro jugador si es el caso
    // ya que el lobby va aceptando de a un solo cliente
    while(not lobby_queue.try_pop(respuesta) && contador < ESPERA_MAXIMA_EN_LOBBY && lobby_abierto){
        std::this_thread::sleep_for(std::chrono::milliseconds((int)500));
        contador++;
    }

    if(respuesta == NULL)
        return  cerrarCliente(c);

    if (respuesta->return_code() == LISTA_DE_PARTIDAS_CODE)
        agregarClienteAPartida(c, respuesta);
    else
        crearNuevaPartida(c, respuesta);
}

void Lobby::newClient(Socket *s)
{
    id_cliente++;

    ServerClient *c = new ServerClient(s, &lobby_queue, id_cliente);
    c->start();

    addToPartida(c);
    c = NULL; // vacio la referencia al cliente.
}

void Lobby::removerPartidasMuertas()
{
    partidas.remove_if([&](Partida *p)
                       {
            if (p->is_dead()){
                p->finish(); 
                p->join();
                delete p;
                return true;
            }
            return false; });
}

void Lobby::reap_dead() { removerPartidasMuertas(); }

void Lobby::cerrarCliente(ServerClient *c){
    std::shared_ptr<Dto> fin = std::make_shared<Dto>(FINALIZAR_CODE);
    c->sender_queue.push(fin);
    c->kill();
    c->join();
    delete c;
}

void Lobby::kill()
{
    lobby_abierto = false;
    for (Partida *p : partidas)
    {
        p->forceFinish();
        delete p;
    }

    partidas.clear();
}
