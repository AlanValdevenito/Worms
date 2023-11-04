#include "client_sender.h"

SenderTH::SenderTH(ClientProtocol &p, Queue<std::shared_ptr<Dto>> &q) : protocol(p), queue(q), was_closed(false) {}

void SenderTH::run()
{
    bool se_envia;
    while (not was_closed)
    {
        std::shared_ptr<Dto> dto = queue.pop();

        if (dto->is_alive())
        {
            se_envia = send(dto);
            if (not se_envia) // si la informacion no se envio correctamente sale del bucle
                break;
        }
        else
        {
            was_closed = true;
        }
    }
    // salgo ordenadamente
}

bool SenderTH::send(std::shared_ptr<Dto> d)
{
    if (d->return_code() == MOVER_A_DERECHA_CODE)
        return protocol.moverADerecha(std::dynamic_pointer_cast<MoverADerecha>(d), was_closed);
    else if (d->return_code() == MOVER_A_IZQUERDA_CODE)
        return protocol.moverAIzquierda(std::dynamic_pointer_cast<MoverAIzquierda>(d), was_closed);
    else if (d->return_code() == LISTA_DE_PARTIDAS_CODE)
        return protocol.enviarSeleccion(std::dynamic_pointer_cast<ListaDePartidas>(d), was_closed);
    else if (d->return_code() == BATEAR_CODE)
        return protocol.enviarAtaqueConBate(std::dynamic_pointer_cast<Batear>(d), was_closed);
    else
        std::cerr << "Codigo de envio desconocido\n";
    return false;
}
