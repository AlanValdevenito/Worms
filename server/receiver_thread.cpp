#include "receiver_thread.h"

void Receiver::run()
{
    while (not was_closed)
    {
        Dto *dto = protocol.recv(was_closed);
        // std::cout << "server recv : " << dto->return_code() << std::endl;
        printf("return code: %u\n",dto->return_code());

        if (dto->is_alive())
        {
            queue.push(dto);
        }
        else
        {
            was_closed = true;
            delete dto;
        }
    }
    broadcaster.removeQueueFromList(&queue);
    // broadcaster.addMessageToQueues();
}

Receiver::Receiver(ServerProtocol &p, Queue<Dto *> &q, Broadcaster &b) : protocol(p), queue(q), broadcaster(b), was_closed(false) {}
