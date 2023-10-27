#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include <cstring>
#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "socket.h"
#include "thread.h"
#include "queue.h"
#include "dto.h"
#include "gusano.h"
#include "server_protocol.h"

const uint8_t VIGA = 1;
const uint8_t WORM = 2;

class Sender : public Thread
{
private:
    ServerProtocol &protocol;
    Queue<Dto *> &queue;
    void send(Dto *d);

public:
    bool was_closed;

    Sender(ServerProtocol &p, Queue<Dto *> &q);
    void run() override;
};

#endif