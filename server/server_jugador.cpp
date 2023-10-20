#include "server_jugador.h"

#include <list>

Jugador::Jugador(Socket&& socket, Queue<Mensaje>& queue, OutgoingQueuesMonitor& outgoing_queues):
        socket(std::move(socket)),
        protocolo(this->socket),
        queue(queue),
        receiver(this->protocolo, this->queue, outgoing_queues),
        sender(this->protocolo, this->queue) {}

void Jugador::start() {
    this->receiver.start();
    this->sender.start();
}

bool Jugador::is_dead() { return this->receiver.is_dead() and this->sender.is_dead(); }

void Jugador::kill() {
    this->receiver.kill();
    this->sender.kill();

    try {
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
    } catch (const std::exception& excepcion) {
        this->socket.close();
    }
}

void Jugador::join() {
    this->receiver.join();
    this->sender.join();

    delete &this->queue;
}
