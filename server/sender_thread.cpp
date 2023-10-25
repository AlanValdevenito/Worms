#include "sender_thread.h"

Sender::Sender(ServerProtocol &p, BlockingQueue &q) : protocol(p), queue(q), was_closed(false) {}

void Sender::run()
{
    while (not was_closed)
    {
        std::cout << "sender\n";
        Dto *dto = queue.pop();

        // protocol.send(was_closed, dto);
        if (dto->is_alive())
            std::cout << "hola\n";
        else
            was_closed = true;

        delete dto;
    }
}
