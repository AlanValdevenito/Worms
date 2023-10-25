#include "client_receiver.h"

ReceiverTH::ReceiverTH(ClientProtocol &p, BlockingQueue &q) : protocol(p), queue(q), was_closed(false) {}

void ReceiverTH::run()
{
    while (not was_closed)
    {

        // Dto *dto = protocol.receive(was_closed);
        Dto *dto = queue.pop();

        if (dto->is_alive())
        {
            std::cout << "recv: " << dto->return_code() << std::endl;
            // lo recibo del lado del cliente
            // queue.push(dto);
        }
        else
        {
            was_closed = true;
            delete dto;
        }
    }
}
