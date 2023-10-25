#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "blockingqueue.h"
#include "broadcaster.h"
#include "dto.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"

class Receiver : public Thread
{
private:
    ServerProtocol &protocol;
    BlockingQueue &queue;
    Broadcaster &broadcaster;

public:
    bool was_closed;

    Receiver(ServerProtocol &p, BlockingQueue &q, Broadcaster &b);
    void run() override;
};
#endif
