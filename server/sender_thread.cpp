#include "sender_thread.h"

Sender::Sender(ServerProtocol &p, Queue<std::shared_ptr<Dto>> &q) : protocol(p), queue(q), was_closed(false) {}

void Sender::run()
{
    while (not was_closed)
    {
        std::shared_ptr<Dto> dto = queue.pop();

        if (dto->is_alive())
            send(dto);
        else
            was_closed = true;

        // delete dto;
    }
}

void Sender::send(std::shared_ptr<Dto> d)
{
    if (d->return_code() == CLIENTE_ID_CODE)
        protocol.sendId(std::dynamic_pointer_cast<ClienteId>(d), was_closed);
    else if (d->return_code() == VIGA_CODE)
        protocol.sendVigas(d, was_closed);
    else if (d->return_code() == GUSANO_CODE)
        protocol.sendWorms(std::dynamic_pointer_cast<Gusano>(d), was_closed);
    else if (d->return_code() == GUSANOS_CODE)
        protocol.sendAllWorms(std::dynamic_pointer_cast<Gusanos>(d), was_closed);
    else if (d->return_code() == LISTA_DE_PARTIDAS_CODE)
        protocol.sendPartidas(std::dynamic_pointer_cast<ListaDePartidas>(d), was_closed);
    else if (d->return_code() == INICIAR_PARIDA)
        protocol.sendIniciarPartida(d, was_closed);
    else
        std::cerr << "Codigo de envio desconocido\n";
}
