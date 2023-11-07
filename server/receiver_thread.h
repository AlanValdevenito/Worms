#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include <iostream>
#include <list>
#include <thread>
#include <vector>
#include <memory>

#include <netinet/in.h>

#include "broadcaster.h"
#include "dto.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"
#include "queue.h"
#include "dto.h"

class Receiver : public Thread
{
private:
    ServerProtocol &protocol;
    Queue<std::shared_ptr<Dto>> *queue;
    // Queue<std::shared_ptr<Dto>> &lobby_queue;

public:
    bool was_closed;

    // Receiver(ServerProtocol &p, Queue<std::shared_ptr<Dto>> &q, Queue<std::shared_ptr<Dto>> &lq);
    Receiver(ServerProtocol &p, Queue<std::shared_ptr<Dto>> *q);
    void run() override;
    void changeReceiverQueue(Queue<std::shared_ptr<Dto>> *q);
};
#endif
