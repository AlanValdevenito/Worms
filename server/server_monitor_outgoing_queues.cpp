#include "server_monitor_outgoing_queues.h"

#include <iostream>

OutgoingQueuesMonitor::OutgoingQueuesMonitor(): contador(0) {}

void OutgoingQueuesMonitor::agregar(Queue<Mensaje>* queue) {
    std::lock_guard<std::mutex> l(this->m);
    this->queues.push_back(queue);
    this->contador++;
}

void OutgoingQueuesMonitor::remover(Queue<Mensaje>* queue) {
    std::lock_guard<std::mutex> l(this->m);
    this->queues.remove(queue);
    this->contador--;
}

void OutgoingQueuesMonitor::broadcast(const Mensaje& mensaje) {
    std::lock_guard<std::mutex> l(this->m);

    for (Queue<Mensaje>* q: this->queues) {
        q->push(mensaje);
    }
}

int OutgoingQueuesMonitor::get_contador() {
    std::lock_guard<std::mutex> l(this->m);
    return this->contador;
}
