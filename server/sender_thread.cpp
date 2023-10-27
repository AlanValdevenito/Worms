#include "sender_thread.h"

Sender::Sender(ServerProtocol &p, Queue<Dto *> &q) : protocol(p), queue(q), was_closed(false) {}

void Sender::run()
{
    while (not was_closed)
    {
        Dto *dto = queue.pop();

        if (dto->is_alive())
            send(dto);
        else
            was_closed = true;

        delete dto;
    }
}

void Sender::send(Dto *d)
{
    if (d->return_code() == VIGA)
        protocol.sendVigas(d, was_closed);
    else if (d->return_code() == WORM)
        protocol.sendWorms((Gusano *)d, was_closed);
    else
        std::cerr << "Codigo de envio desconocido\n";
}
