#include "receiver_thread.h"

void Receiver::run()
{
    while (not was_closed)
    {
        Dto *dto = protocol.recv(was_closed);
        // std::cout << "server recv : " << dto->return_code() << std::endl;
        // printf("return code: %u\n", dto->return_code());

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
            delete dto;
        }
    }
}

Receiver::Receiver(ServerProtocol &p, Queue<Dto *> &q, Queue<Dto *> &lq) : protocol(p), queue(q), lobby_queue(lq), was_closed(false) {}
