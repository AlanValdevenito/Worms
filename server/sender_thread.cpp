#include "sender_thread.h"

Sender::Sender(ServerProtocol &p, BlockingQueue &q) : protocol(p), queue(q), was_closed(false) {}

void Sender::run()
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
