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

struct Receiver : public Thread
{
private:
    ServerProtocol &protocol;
    BlockingQueue &queue;
    Broadcaster &broadcaster;

public:
    bool was_closed;
    void run() override
    {
        while (not was_closed)
        {
            Dto *dto = protocol.decode(was_closed);

            if (dto->is_alive())
            {
                std::cout << dto->message() << std::endl; // proteger
                broadcaster.addMessageToQueues(dto);
            }
            else
            {
                was_closed = true;
                delete dto;
            }
        }
        broadcaster.removeQueueFromList(&queue);
        broadcaster.addMessageToQueues();
    }

    Receiver(ServerProtocol &p, BlockingQueue &q, Broadcaster &b) : protocol(p), queue(q), broadcaster(b), was_closed(false) {}
};
