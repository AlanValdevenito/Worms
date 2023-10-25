#include "client_sender.h"

SenderTH::SenderTH(ClientProtocol &p, BlockingQueue &q, Broadcaster &b) : protocol(p), queue(q), broadcaster(b), was_closed(false) {}

void SenderTH::run()
{
    std::string data;
    while (not was_closed)
    {
        Dto *dto = queue.pop();

        // protocol.sendChatMsj(dto->message(), was_closed);
        if (dto->is_alive()) // se lo mando al protocolo
            std::cout << "send: " << std::endl;
        else
            was_closed = true;

        delete dto;
    }
}
