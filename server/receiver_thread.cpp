#include "receiver_thread.h"

void Receiver::run()
{
    while (not was_closed)
    {
        std::shared_ptr<Dto> dto = protocol.recv(was_closed);

        if (dto->is_alive())
        {
            if (dto->return_code() == LISTA_DE_PARTIDAS_CODE)
                lobby_queue.push(dto);
            else
                queue.push(dto);
        }
        else
        {
            was_closed = true;
            // delete dto;
        }
    }
}

Receiver::Receiver(ServerProtocol &p, Queue<std::shared_ptr<Dto>> &q, Queue<std::shared_ptr<Dto>> &lq) : protocol(p), queue(q), lobby_queue(lq), was_closed(false) {}
