#ifndef SERVIDOR_JUGADOR_H
#define SERVIDOR_JUGADOR_H

#include <utility>

#include "server_receiver.h"
#include "server_sender.h"

class Jugador {
private:
    Socket socket;
    ProtocoloServidor protocolo;

    Queue<Mensaje>& queue;

    ServidorReceiver receiver;
    ServidorSender sender;

public:
    Jugador(Socket&& socket, Queue<Mensaje>& queue, OutgoingQueuesMonitor& outgoing_queues);

    void start();
    bool is_dead();
    void kill();
    void join();

    Jugador(const Jugador&) = delete;
    Jugador& operator=(const Jugador&) = delete;

    Jugador(Jugador&&);
    Jugador& operator=(Jugador&&);
};

#endif
