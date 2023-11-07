#include "receiver_thread.h"

void Receiver::run()
{
    while (not was_closed)
    {
        std::shared_ptr<Dto> dto = protocol.recibirActividad(was_closed);

        if (dto->is_alive())
        {
            queue->push(dto);
            // if (dto->return_code() == LISTA_DE_PARTIDAS_CODE)
            //     lobby_queue.push(dto);
            // else
            //     queue.push(dto);
        }
        else
        {
            was_closed = true;
            // queue.push(dto); // le informo que el cliente se desconecto
        }
    }
    // std::cout << "sale del recv del server\n";
}

// Receiver::Receiver(ServerProtocol &p, Queue<std::shared_ptr<Dto>> &q, Queue<std::shared_ptr<Dto>> &lq) : protocol(p), queue(q), lobby_queue(lq), was_closed(false) {}
Receiver::Receiver(ServerProtocol &p, Queue<std::shared_ptr<Dto>> *q) : protocol(p), queue(q), was_closed(false) {}

void Receiver::changeReceiverQueue(Queue<std::shared_ptr<Dto>> *q) { 
    std::cout<<"queue antes: " << queue<< std::endl;
    queue = q; 
    std::cout<<"queue despues: " << queue<< std::endl;}
