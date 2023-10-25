#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include <cstring>
#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "blockingqueue.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"

class Sender : public Thread
{
private:
    ServerProtocol &protocol;
    BlockingQueue &queue;

public:
    bool was_closed;

    Sender(ServerProtocol &p, BlockingQueue &q);
    void run() override;
};

#endif
