#include "server_monitor_outgoing_queues.h"

#include <iostream>

OutgoingQueuesMonitor::OutgoingQueuesMonitor() {}

void OutgoingQueuesMonitor::agregar(Queue<std::shared_ptr<Dto>> *queue)
{
    std::lock_guard<std::mutex> l(this->m);
    this->queues.push_back(queue);
}

void OutgoingQueuesMonitor::remover(Queue<std::shared_ptr<Dto>> *queue)
{
    std::lock_guard<std::mutex> l(this->m);
    this->queues.remove(queue);
}

std::list<Queue<std::shared_ptr<Dto>> *> OutgoingQueuesMonitor::listado()
{
    return queues;
}
