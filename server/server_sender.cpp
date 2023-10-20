#include "server_sender.h"

#define MENSAJE_CANTIDAD_JUGADORES 6
#define MENSAJE_CHAT 5

ServidorSender::ServidorSender(ProtocoloServidor& protocolo, Queue<Mensaje>& queue):
        protocolo(protocolo), queue(queue) {}

void ServidorSender::run() {
    this->is_alive = this->keep_talking = true;

    while (this->keep_talking) {

        try {
            Mensaje mensaje = this->queue.pop();

            if (mensaje.tipo == MENSAJE_CANTIDAD_JUGADORES) {
                this->protocolo.enviar_cantidad_de_jugadores(mensaje);

            } else if (mensaje.tipo == MENSAJE_CHAT) {
                this->protocolo.enviar_mensaje_de_chat(mensaje);
            }

        } catch (const ClosedQueue& excepcion) {
            this->is_alive = false;
            break;
        }
    }

    this->is_alive = false;
}

bool ServidorSender::is_dead() { return not this->is_alive; }

void ServidorSender::kill() { this->keep_talking = false; }
