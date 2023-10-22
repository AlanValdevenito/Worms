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

struct Sender : public Thread
{
private:
    ServerProtocol &protocol;
    BlockingQueue &queue;

public:
    bool was_closed;

    void run() override
    {
        while (not was_closed)
        {
            Dto *dto = queue.pop();

            if (dto->is_alive())
                protocol.send(was_closed, dto);
            else
                was_closed = true;

            delete dto;
        }
    }

    Sender(ServerProtocol &p, BlockingQueue &q) : protocol(p), queue(q), was_closed(false) {}
};
