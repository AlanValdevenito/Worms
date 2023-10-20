#include "server_receiver.h"

#define MENSAJE_CANTIDAD_JUGADORES 6

ServidorReceiver::ServidorReceiver(ProtocoloServidor& protocolo, Queue<Mensaje>& queue,
                                   OutgoingQueuesMonitor& outgoing_queues):
        protocolo(protocolo), queue(queue), outgoing_queues(outgoing_queues) {}

void ServidorReceiver::run() {
    bool was_closed = false;
    this->is_alive = this->keep_talking = true;

    while (not was_closed and this->keep_talking) {
        Mensaje mensaje = this->protocolo.esperar_mensaje_de_chat(&was_closed);

        if (was_closed or not this->keep_talking) {
            this->outgoing_queues.remover(&this->queue);

            imprimir_cantidad_de_jugadores();

            Mensaje cantidad_de_jugadores = {MENSAJE_CANTIDAD_JUGADORES,
                                             std::to_string(this->outgoing_queues.get_contador())};
            this->outgoing_queues.broadcast(cantidad_de_jugadores);
            break;
        }

        imprimir_mensaje_de_chat(mensaje);
        this->outgoing_queues.broadcast(mensaje);
    }

    this->is_alive = false;
    this->queue.close();
}

bool ServidorReceiver::is_dead() { return not this->is_alive; }

void ServidorReceiver::kill() { this->keep_talking = false; }

void ServidorReceiver::imprimir_mensaje_de_chat(const Mensaje& mensaje) {
    std::ostringstream oss;
    oss << mensaje.msg << std::endl;
    std::cout << oss.str();
}

void ServidorReceiver::imprimir_cantidad_de_jugadores() {
    std::ostringstream oss;
    oss << "Jugadores " << std::to_string(this->outgoing_queues.get_contador())
        << ", esperando al resto de tus amigos..." << std::endl;
    std::cout << oss.str();
}
