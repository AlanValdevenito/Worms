#include "server_monitor_outgoing_queues.h"

#include <iostream>

OutgoingQueuesMonitor::OutgoingQueuesMonitor() {}

void OutgoingQueuesMonitor::agregar(Queue<std::shared_ptr<Dto>> *queue, uint8_t id)
{
    std::lock_guard<std::mutex> l(this->m);
    this->queues.push_back(queue);
    this->id_queues[id] = queue;
}

void OutgoingQueuesMonitor::remover(Queue<std::shared_ptr<Dto>> *queue){

    std::lock_guard<std::mutex> l(this->m);
    this->queues.remove(queue);
}

Queue<std::shared_ptr<Dto>> * OutgoingQueuesMonitor::remover(uint8_t id)
{
    std::lock_guard<std::mutex> l(this->m);


    Queue<std::shared_ptr<Dto>> *queue = this->id_queues[id];

    this->queues.remove(queue);
    this->id_queues.erase(id);
    
    return queue;
}

void OutgoingQueuesMonitor::removeAllQueues(){

    //recorro por id y elimino
    for (const auto &elemento : this->id_queues)
        this->queues.remove(this->id_queues[elemento.first]);

    this->id_queues.clear();
}

std::list<Queue<std::shared_ptr<Dto>> *> OutgoingQueuesMonitor::listado()
{
    return queues;
}
