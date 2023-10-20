#ifndef SERVIDOR_SENDER_H
#define SERVIDOR_SENDER_H

#include <atomic>
#include <list>

#include "common_queue.h"
#include "server_monitor_outgoing_queues.h"
#include "server_protocolo.h"
#include "common_thread.h"

class ServidorSender: public Thread {
private:
    ProtocoloServidor& protocolo;
    Queue<Mensaje>& queue;

    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    ServidorSender(ProtocoloServidor& protocolo, Queue<Mensaje>& queue);

    virtual void run() override;
    bool is_dead();
    void kill();
    void imprimir_mensaje_de_chat(const Mensaje& mensaje);
};

#endif
