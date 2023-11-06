#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <memory>

#include "queue.h"
#include "dto.h"
#include "viga.h"
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
    void AddGusanosToQueues(std::shared_ptr<Gusanos> gs);
    void AddGusanoToQueues(std::shared_ptr<Gusano> g);
    void AddVigasToQueues(std::shared_ptr<Vigas> vs);
    void addQueueToList(Queue<std::shared_ptr<Dto>> &q, uint8_t id);
    void removeQueueFromList(Queue<std::shared_ptr<Dto>> *q);
    void removeQueueWithId(uint8_t id);
    void deleteAllQueues();
    void notificarCierre(std::shared_ptr<Dto> dto);
};
#endif
