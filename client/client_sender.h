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
#include "queue.h"
#include "thread.h"
#include "client_protocol.h"
#include "constantes.h"
#include "dto.h"
#include "mover.h"

struct SenderTH : public Thread
{
private:
    ClientProtocol &protocol;
    Queue<Dto *> &queue;
    Broadcaster &broadcaster;

public:
    bool was_closed;

    SenderTH(ClientProtocol &p, Queue<Dto *> &q, Broadcaster &b);
    void run() override;
    void send(Dto *d);
};

#endif
