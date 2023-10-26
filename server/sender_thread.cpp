#include "sender_thread.h"

Sender::Sender(ServerProtocol &p, Queue<Dto *> &q) : protocol(p), queue(q), was_closed(false) {}

void Sender::run()
{
    while (not was_closed)
    {
        Dto *dto = queue.pop();

        if (dto->is_alive())
            protocol.sendViga(dto, was_closed);
        else
            was_closed = true;

        delete dto;
    }
}
