#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <iostream>
#include <list>
#include <thread>
#include <vector>
#include <memory>

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
    Queue<std::shared_ptr<Dto>> &queue;

public:
    bool was_closed;

    ReceiverTH(ClientProtocol &p, Queue<std::shared_ptr<Dto>> &q);
    void run() override;
};
#endif
