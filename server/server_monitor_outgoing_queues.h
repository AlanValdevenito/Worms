#ifndef SERVIDOR_MONITOR_OUTGOING_QUEUES_H
#define SERVIDOR_MONITOR_OUTGOING_QUEUES_H

#include <list>
#include <mutex>

#include "common_queue.h"
#include "server_protocolo.h"

class OutgoingQueuesMonitor {
private:
    int contador;

    std::list<Queue<Mensaje>*> queues;
    std::mutex m;

public:
    OutgoingQueuesMonitor();

    void agregar(Queue<Mensaje>* queue);
    void remover(Queue<Mensaje>* queue);
    void broadcast(const Mensaje& mensaje);

    int get_contador();
};

#endif
