#ifndef SERVIDOR_MONITOR_OUTGOING_QUEUES_H
#define SERVIDOR_MONITOR_OUTGOING_QUEUES_H

#include <list>
#include <mutex>

#include "queue.h"
#include "dto.h"

class OutgoingQueuesMonitor
{
private:
    std::list<Queue<Dto *> *> queues;
    std::mutex m;

public:
    OutgoingQueuesMonitor();

    void agregar(Queue<Dto *> *queue);
    void remover(Queue<Dto *> *queue);
    std::list<Queue<Dto *> *> listado();
    // void broadcast(const Mensaje &mensaje);

    // int get_contador();
};

#endif
