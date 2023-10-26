#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "blockingqueue.h"
#include "broadcaster.h"
#include "dto.h"
#include "socket.h"
#include "queue.h"
#include "thread.h"
#include "client_protocol.h"

struct ReceiverTH : public Thread
{
private:
    ClientProtocol &protocol;
    Queue<Dto *> &queue;

public:
    bool was_closed;

    ReceiverTH(ClientProtocol &p, Queue<Dto *> &q);
    void run() override;
};
#endif
