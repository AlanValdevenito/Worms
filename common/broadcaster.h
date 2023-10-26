#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <iostream>
#include <list>
#include <mutex>
#include <string>

#include "blockingqueue.h"
#include "dto.h"
#include "server_protocol.h"

class Broadcaster
{
private:
    std::list<BlockingQueue *> queues;
    std::mutex mutex;

public:
    void addMessageToQueues();
    void addMessageToQueues(Dto *dto);
    void addVigaToQueues(Dto *dto);
    void addQueueToList(BlockingQueue &q);
    void removeQueueFromList(BlockingQueue *q);
    void deleteAllQueues();
};
#endif
