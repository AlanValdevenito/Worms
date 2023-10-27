#include "client_receiver.h"

ReceiverTH::ReceiverTH(ClientProtocol &p, Queue<Dto *> &q) : protocol(p), queue(q), was_closed(false) {}

void ReceiverTH::run()
{
    while (not was_closed)
    {

        Dto *dto = protocol.receive(was_closed);

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
}
