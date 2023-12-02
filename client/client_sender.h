#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <cstring>
#include <iostream>
#include <list>
#include <thread>
#include <vector>
#include <memory>

#include <netinet/in.h>

#include "broadcaster.h"
#include "socket.h"
#include "queue.h"
#include "thread.h"
#include "client_protocol.h"
#include "constantes.h"
#include "dto.h"
#include "mover.h"
#include "batear.h"

struct SenderTH : public Thread
{
private:
    ClientProtocol &protocol;
    Queue<std::shared_ptr<Dto>> &queue;
    bool is_attak(std::shared_ptr<Dto> d);
    bool is_a_move(std::shared_ptr<Dto> d);

public:
    bool was_closed;

    SenderTH(ClientProtocol &p, Queue<std::shared_ptr<Dto>> &q);
    void run() override;
    bool send(std::shared_ptr<Dto> d);
};

#endif
