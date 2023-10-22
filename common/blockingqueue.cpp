#include "blockingqueue.h"

BlockingQueue::BlockingQueue() {}

BlockingQueue::~BlockingQueue() {}

/*
 * COMENTARIO:
 * Podria tener una capacidad maxima ya que esta ocupando memoria y siempre hay un limite de
 * memoria, pero para esta implementacion no me parecio necesaria. Sin embargo, que tenga una
 * capacidad maxima de almacenamiento podria no afectar a la performance del modelo ya que depende
 * de la cantidad de clientes que se tengan en simultaneo. Creo que seria conveniente que la
 * capacidad maxima sea variable a la cantidad de usuarios conectados en un determinado momento,
 * pensando en que solo llegaria a su tope si todos los usuarios envian un mensaje al mismo tiempo.
 */
void BlockingQueue::push(Dto *element)
{
    std::unique_lock<std::mutex> lock(mutex);
    // while (internal.size() == max_size) {
    //     cv_not_full.wait(lock);
    // }
    internal.push(element);
    // internal.push_back(element);
    cv.notify_all();
}

Dto *BlockingQueue::pop()
{
    std::unique_lock<std::mutex> lock(mutex);
    while (internal.empty())
    {
        cv.wait(lock);
    }
    Dto *element(internal.front());
    internal.pop();
    return element;
}

void BlockingQueue::clear()
{
    std::unique_lock<std::mutex> lock(mutex);
    while (internal.size() > 0)
    {
        internal.pop();
    }
}
