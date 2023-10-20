#ifndef SERVIDOR_ACEPTADOR_H
#define SERVIDOR_ACEPTADOR_H

#include <list>
#include <utility>

#include "server_jugador.h"

class Aceptador: public Thread {
private:
    Socket& socket;

    OutgoingQueuesMonitor outgoing_queues;
    std::list<Jugador*> jugadores;

public:
    explicit Aceptador(Socket& socket);

    virtual void run() override;

    void reap_dead();
    void kill_all();

    void imprimir_cantidad_de_jugadores();
};

#endif
