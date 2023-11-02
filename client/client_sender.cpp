#include "client_sender.h"

SenderTH::SenderTH(ClientProtocol &p, Queue<std::shared_ptr<Dto>> &q) : protocol(p), queue(q), was_closed(false) {}

void SenderTH::run()
{
    std::string data;
    while (not was_closed)
    {
        std::shared_ptr<Dto> dto = queue.pop();
        // std::cout << "send: " << dto->is_alive() << std::endl;

        if (dto->is_alive())
        {
            send(dto);
            protocol.send(was_closed);
        } // se lo mando al protocolo
        else
            was_closed = true;

        // delete dto;
    }
}

void SenderTH::send(std::shared_ptr<Dto> d)
{
    if (d->return_code() == MOVER_A_DERECHA_CODE)
        protocol.moverADerecha(std::dynamic_pointer_cast<MoverADerecha>(d), was_closed);
    else if (d->return_code() == MOVER_A_IZQUERDA_CODE)
        protocol.moverAIzquierda(std::dynamic_pointer_cast<MoverAIzquierda>(d), was_closed);
    else if (d->return_code() == LISTA_DE_PARTIDAS_CODE)
        protocol.enviarSeleccion(std::dynamic_pointer_cast<ListaDePartidas>(d), was_closed);
    else
        std::cerr << "Codigo de envio desconocido\n";
}
