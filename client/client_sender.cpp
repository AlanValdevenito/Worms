#include "client_sender.h"

SenderTH::SenderTH(ClientProtocol &p, Queue<std::shared_ptr<Dto>> &q) : protocol(p), queue(q), was_closed(false) {}

void SenderTH::run()
{
    while (not was_closed)
    {
        std::shared_ptr<Dto> dto = queue.pop();

        if (dto->is_alive())
        {
            if (not send(dto)) // si la informacion no se envio correctamente sale del bucle
                break;
        }
        else
        {
            was_closed = true;
        }
    }
    std::cerr << "El hilo sender fue cerrado por enviar informacion desconocida\n";
}

bool SenderTH::send(std::shared_ptr<Dto> d)
{
    if (is_a_move(d))
        return protocol.enviarMovimiento(d, was_closed);
    else if (is_attak(d))
        return protocol.enviarAtaque(d, was_closed);
    else if (d->return_code() == LISTA_DE_PARTIDAS_CODE)
        return protocol.enviarSeleccion(std::dynamic_pointer_cast<ListaDePartidas>(d), was_closed);
    else if (d->return_code() == FINALIZAR_CODE)
        return protocol.enviarFinDePartida(d, was_closed);
    else if (d->return_code() == NUEVA_PARTIDA_CODE)
        return protocol.enviarNuevaPartida(std::dynamic_pointer_cast<NuevaPartida>(d), was_closed);
    else if (d->return_code() == EQUIPAR_ARMA_CODE)
        return protocol.enviarEquipadoDeArma(std::dynamic_pointer_cast<EquiparArma>(d), was_closed);
    else if (d->return_code() == CHEAT_CODE)
        return protocol.enviarCheat(std::dynamic_pointer_cast<Cheat>(d), was_closed);
    else
        std::cerr << "Codigo de envio desconocido\n";
    return false;
}

bool SenderTH::is_attak(std::shared_ptr<Dto> d){
    uint8_t code = d->return_code();
    bool es_granada = (code == GRANADA_VERDE_CODE || code == GRANADA_BANANA_CODE || code == GRANADA_SANTA_CODE || code == GRANADA_ROJA_CODE);
    return ( es_granada || code == BAZUKA_CODE || code == MORTERO_CODE || code == DINAMITA_CODE || code == BATEAR_CODE || code == ATAQUE_AEREO_CODE);
}

bool SenderTH::is_a_move(std::shared_ptr<Dto> d){
    uint8_t code = d->return_code();
    return ( code == MOVER_A_DERECHA_CODE || code == MOVER_A_IZQUIERDA_CODE || code == SALTAR_CODE || code == TELETRANSPORTAR_CODE);
}