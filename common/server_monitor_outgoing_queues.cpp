#include "server_monitor_outgoing_queues.h"

#include <iostream>

OutgoingQueuesMonitor::OutgoingQueuesMonitor() {}

/* Se agrega la cola recibida a la lista de colas y se agrega la cola a un diccionario
 * donde la key es el id del cliente
 */
void OutgoingQueuesMonitor::agregar(Queue<std::shared_ptr<Dto>> *queue, uint8_t id)
{
    std::lock_guard<std::mutex> l(this->m);
    this->queues.push_back(queue);
    this->id_queues[id] = queue;
}

void OutgoingQueuesMonitor::remover(Queue<std::shared_ptr<Dto>> *queue)
{

    std::lock_guard<std::mutex> l(this->m);
    this->queues.remove(queue);
}

Queue<std::shared_ptr<Dto>> *OutgoingQueuesMonitor::remover(uint8_t id)
{
    std::lock_guard<std::mutex> l(this->m);

    Queue<std::shared_ptr<Dto>> *queue = this->id_queues[id];

    this->queues.remove(queue); // elimino la cola de la lista
    this->id_queues.erase(id);  // elimino la cola del diccionario

    return queue;
}

void OutgoingQueuesMonitor::removeAllQueues()
{

    // recorro por id y elimino
    for (const auto &elemento : this->id_queues)
        this->queues.remove(this->id_queues[elemento.first]); // elimino todas las colas dela lista

    this->id_queues.clear(); // vacio el diccionario perdiendo la referencia a las colas
}

std::list<Queue<std::shared_ptr<Dto>> *> OutgoingQueuesMonitor::listado()
{
    return queues;
}
