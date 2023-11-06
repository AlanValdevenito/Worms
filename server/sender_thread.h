#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include <cstring>
#include <iostream>
#include <list>
#include <thread>
#include <vector>
#include <memory>

#include <netinet/in.h>

#include "socket.h"
#include "thread.h"
#include "queue.h"
#include "constantes.h"
#include "dto.h"
#include "gusano.h"
#include "partidas_lista.h"
#include "cliente_id.h"
#include "server_protocol.h"

class Sender : public Thread
{
private:
    ServerProtocol &protocol;
    Queue<std::shared_ptr<Dto>> &queue;
    bool send(std::shared_ptr<Dto> d);

public:
    bool was_closed;

    Sender(ServerProtocol &p, Queue<std::shared_ptr<Dto>> &q);
    void run() override;
};

#endif
