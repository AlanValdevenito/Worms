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
    std::cout << "sale del sender del cliente\n";
    // salgo ordenadamente
}

bool SenderTH::send(std::shared_ptr<Dto> d)
{

    if (d->return_code() == MOVER_A_DERECHA_CODE)
        return protocol.moverADerecha(std::dynamic_pointer_cast<MoverADerecha>(d), was_closed);
    else if (d->return_code() == MOVER_A_IZQUIERDA_CODE)
        return protocol.moverAIzquierda(std::dynamic_pointer_cast<MoverAIzquierda>(d), was_closed);
    else if (d->return_code() == LISTA_DE_PARTIDAS_CODE)
        return protocol.enviarSeleccion(std::dynamic_pointer_cast<ListaDePartidas>(d), was_closed);
    else if (d->return_code() == BATEAR_CODE)
        return protocol.enviarAtaqueConBate(std::dynamic_pointer_cast<Batear>(d), was_closed);
    else if (d->return_code() == FINALIZAR_CODE)
        return protocol.enviarFinDePartida(d, was_closed);
    else if (d->return_code() == SALTAR_CODE)
        return protocol.saltar(std::dynamic_pointer_cast<Saltar>(d), was_closed);
    else if (d->return_code() == NUEVA_PARTIDA_CODE)
        return protocol.enviarNuevaPartida(std::dynamic_pointer_cast<NuevaPartida>(d), was_closed);
    else if (d->return_code() == GRANADA_VERDE_CODE)
        return protocol.enviarAtaqueConGranadaVerde(std::dynamic_pointer_cast<GranadaVerde>(d), was_closed);
    else if (d->return_code() == BAZUKA_CODE)
        return protocol.enviarAtaqueConBazuka(std::dynamic_pointer_cast<Bazuka>(d), was_closed);
    else if (d->return_code() == GRANADA_BANANA_CODE)
        return protocol.enviarAtaqueConGranadaBanana(std::dynamic_pointer_cast<GranadaBanana>(d), was_closed);
    else if (d->return_code() == GRANADA_SANTA_CODE)
        return protocol.enviarAtaqueConGranadaSanta(std::dynamic_pointer_cast<GranadaSanta>(d), was_closed);
    else if (d->return_code() == DINAMITA_CODE)
        return protocol.enviarAtaqueConDinamita(std::dynamic_pointer_cast<Dinamita>(d), was_closed);
    else if (d->return_code() == DINAMITA_CODE)
        return protocol.enviarAtaqueConDinamita(std::dynamic_pointer_cast<Dinamita>(d), was_closed);
    else if (d->return_code() == TELETRANSPORTAR_CODE)
        return protocol.enviarTeletrasnportacion(std::dynamic_pointer_cast<Teletransportar>(d), was_closed);
    else
        std::cerr << "Codigo de envio desconocido\n";
    return false;
}
