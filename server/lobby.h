#ifndef LOBBY_H
#define LOBBY_H

#include <atomic>
#include <chrono>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <memory>

#include "queue.h"
#include "receiver_thread.h"
#include "sender_thread.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"
#include "server_client.h"
#include "partida.h"
#include "partidas_lista.h"
#include "nueva_partida.h"
#include "game.h"
#include "dto.h"

const int ESPERA_MAXIMA_EN_LOBBY = 40; // 10 (segundos)

class Lobby
{
public:
    Lobby();
    ~Lobby();
    void kill();
    void reap_dead();
    void newClient(Socket *s);

private:
    Queue<std::shared_ptr<Dto>> lobby_queue;
    uint8_t mapId;
    std::list<Partida *> partidas;
    uint8_t id_cliente;
    int partida_id;
    bool lobby_abierto;

    void enviarPartidasDisponibles(ServerClient *c);
    void agregarAUnaPartida(ServerClient *c);
    void cerrarCliente(ServerClient *c);
    void agregarClienteAPartida(ServerClient *c, std::shared_ptr<Dto> lista);
    void crearNuevaPartida(ServerClient *c, std::shared_ptr<Dto> np);
    void removerPartidasMuertas();
};
#endif
