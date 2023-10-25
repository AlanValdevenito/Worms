#include "receiver_thread.h"

void Receiver::run()
{
    while (not was_closed)
    {
        Dto *dto = protocol.recv(was_closed);
        std::cout << "server recv : " << dto->return_code() << std::endl;

        // if (dto->is_alive())
        // {
        //     // std::cout << dto->message() << std::endl; // proteger
        //     // broadcaster.addMessageToQueues(dto);
        // }
        // else
        // {
        //     was_closed = true;
        //     delete dto;
        // }
    }
    broadcaster.removeQueueFromList(&queue);
    // broadcaster.addMessageToQueues();
}

Receiver::Receiver(ServerProtocol &p, BlockingQueue &q, Broadcaster &b) : protocol(p), queue(q), broadcaster(b), was_closed(false) {}
