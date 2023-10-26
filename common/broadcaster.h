#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <iostream>
#include <list>
#include <mutex>
#include <string>

#include "queue.h"
#include "dto.h"
#include "server_monitor_outgoing_queues.h"
#include "server_protocol.h"

class Broadcaster
{
private:
    // std::list<BlockingQueue *> queues;
    OutgoingQueuesMonitor queues;
    std::mutex mutex;

public:
    void addMessageToQueues();
    void addMessageToQueues(Dto *dto);
    void addVigaToQueues(Dto *dto);
    void addQueueToList(Queue<Dto *> &q);
    void removeQueueFromList(Queue<Dto *> *q);
    void deleteAllQueues();
};
#endif
