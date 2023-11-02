#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <memory>

#include "queue.h"
#include "dto.h"
#include "gusano.h"
#include "server_monitor_outgoing_queues.h"
#include "server_protocol.h"
#include "constantes.h"

class Broadcaster
{
private:
    OutgoingQueuesMonitor queues;
    std::mutex mutex;

public:
    void addMessageToQueues();
    // void AddGusanoToQueues(Gusano *g);
    void AddGusanosToQueues2(std::shared_ptr<Gusanos> gs);
    void AddGusanoToQueues2(std::shared_ptr<Gusano> g);
    // void AddGusanosToQueues(Gusanos *gs);
    void AddVigasToQueues2(std::shared_ptr<Vigas> vs);
    // void AddVigasToQueues(Vigas *vs);
    // void addMessageToQueues(std::shared_ptr<Dto> dto);
    // void addVigaToQueues(std::shared_ptr<Dto> dto);
    void addQueueToList(Queue<std::shared_ptr<Dto>> &q);
    void removeQueueFromList(Queue<std::shared_ptr<Dto>> *q);
    void deleteAllQueues();
};
#endif
