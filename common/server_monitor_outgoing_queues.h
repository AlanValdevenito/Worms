#ifndef SERVIDOR_MONITOR_OUTGOING_QUEUES_H
#define SERVIDOR_MONITOR_OUTGOING_QUEUES_H

#include <list>
#include <mutex>
#include <memory>

#include "queue.h"
#include "dto.h"

class OutgoingQueuesMonitor
{
private:
    std::list<Queue<std::shared_ptr<Dto>> *> queues;
    std::mutex m;

public:
    OutgoingQueuesMonitor();

    void agregar(Queue<std::shared_ptr<Dto>> *queue);
    void remover(Queue<std::shared_ptr<Dto>> *queue);
    std::list<Queue<std::shared_ptr<Dto>> *> listado();
};

#endif
