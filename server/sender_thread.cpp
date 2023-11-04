#include "sender_thread.h"

Sender::Sender(ServerProtocol &p, Queue<std::shared_ptr<Dto>> &q) : protocol(p), queue(q), was_closed(false) {}

void Sender::run()
{
    bool se_envio;
    while (not was_closed)
    {
        std::shared_ptr<Dto> dto = queue.pop();

        if (dto->is_alive())
        {
            // std::cout << "entro\n";
            se_envio = send(dto);
            if (not se_envio)
                break;
        }
        else
            was_closed = true;
    }
    std::cout << "salio\n";
    // salgo ordenadamente
}

bool Sender::send(std::shared_ptr<Dto> d)
{
    if (d->return_code() == CLIENTE_ID_CODE)
        return protocol.enviarId(std::dynamic_pointer_cast<ClienteId>(d), was_closed);
    else if (d->return_code() == VIGA_CODE)
        return protocol.enviarVigas(d, was_closed);
    else if (d->return_code() == GUSANO_CODE)
        return protocol.enviarGusano(std::dynamic_pointer_cast<Gusano>(d), was_closed);
    else if (d->return_code() == GUSANOS_CODE)
        return protocol.enviarListaDeGusanos(std::dynamic_pointer_cast<Gusanos>(d), was_closed);
    else if (d->return_code() == LISTA_DE_PARTIDAS_CODE)
        return protocol.enviarListaDePartidas(std::dynamic_pointer_cast<ListaDePartidas>(d), was_closed);
    else if (d->return_code() == INICIAR_PARIDA)
        return protocol.enviarIniciarPartida(d, was_closed);
    else
        std::cerr << "Codigo de envio desconocido\n";
    return false;
}
