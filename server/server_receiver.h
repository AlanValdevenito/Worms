#ifndef SERVIDOR_RECEIVER_H
#define SERVIDOR_RECEIVER_H

#include <atomic>
#include <list>
#include <sstream>

#include "common_queue.h"
#include "server_monitor_outgoing_queues.h"
#include "server_protocolo.h"
#include "common_thread.h"

class ServidorReceiver: public Thread {
private:
    ProtocoloServidor& protocolo;
    Queue<Mensaje>& queue;
    OutgoingQueuesMonitor& outgoing_queues;

    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    ServidorReceiver(ProtocoloServidor& protocolo, Queue<Mensaje>& queue,
                     OutgoingQueuesMonitor& outgoing_queues);

    virtual void run() override;
    bool is_dead();
    void kill();
    void imprimir_mensaje_de_chat(const Mensaje& mensaje);
    void imprimir_cantidad_de_jugadores();
};

#endif
