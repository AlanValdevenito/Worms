#include "client_receiver.h"

ReceiverTH::ReceiverTH(ClientProtocol &p, Queue<std::shared_ptr<Dto>> &q) : protocol(p), queue(q), was_closed(false) {}

void ReceiverTH::run()
{
    while (not was_closed)
    {

        std::shared_ptr<Dto> dto = protocol.receive(was_closed);

        if (dto->is_alive())
        {
            queue.push(dto);
        }
        else
        {
            was_closed = true;
            // delete dto;
        }
    }
}
