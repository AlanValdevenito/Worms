#ifndef SERVIDOR_MONITOR_OUTGOING_QUEUES_H
#define SERVIDOR_MONITOR_OUTGOING_QUEUES_H

#include <list>
#include <mutex>
#include <memory>
#include <map>

#include "queue.h"
#include "dto.h"

class OutgoingQueuesMonitor
{
private:
    std::list<Queue<std::shared_ptr<Dto>> *> queues;
    std::map<uint8_t, Queue<std::shared_ptr<Dto>> *> id_queues;
    std::mutex m;

public:
    OutgoingQueuesMonitor();

    void agregar(Queue<std::shared_ptr<Dto>> *queue, uint8_t id);
    void remover(Queue<std::shared_ptr<Dto>> *queue);
    Queue<std::shared_ptr<Dto>> * remover(uint8_t id);
    std::list<Queue<std::shared_ptr<Dto>> *> listado();
    void removeAllQueues();
};

#endif
