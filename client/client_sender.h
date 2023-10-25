#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <cstring>
#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "broadcaster.h"
#include "blockingqueue.h"
#include "socket.h"
#include "thread.h"
#include "client_protocol.h"

const char CHAT[] = "Chat";
const char READ[] = "Read";
const char EXIT[] = "Exit";

struct SenderTH : public Thread
{
private:
    ClientProtocol &protocol;
    BlockingQueue &queue;
    Broadcaster &broadcaster;

public:
    bool was_closed;

    SenderTH(ClientProtocol &p, BlockingQueue &q, Broadcaster &b);
    void run() override;
};

#endif
