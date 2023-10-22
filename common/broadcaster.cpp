#include "broadcaster.h"

/*
 *   Crea un Dto y agrega a todas las colas una instancia nueva del dto
 *   Luego lo elimina del HEAP
 */
void Broadcaster::addMessageToQueues()
{
    std::unique_lock<std::mutex> lock(mutex);
    Dto *dto = new PlayersMessage(static_cast<uint8_t>(queues.size()));
    for (auto q : queues)
    {
        Dto *d = new PlayersMessage(static_cast<uint8_t>(queues.size()));
        q->push(d);
    }

    std::cout << dto->message() << std::endl;

    delete dto;
}

/*
 *   Por cada cola, crea una nueva instancia del Dto recibido, y se lo agrega a todas.
 *   Luego lo elimina el Dto original del HEAP
 *   (Se que solo llegaran a este metodos mensajes de tipo chat)
 */
void Broadcaster::addMessageToQueues(Dto *dto)
{
    std::unique_lock<std::mutex> lock(mutex);
    for (auto q : queues)
    {
        Dto *d = new ChatMessage(dto->message());
        q->push(d);
    }
    delete dto;
}

/*
 *  Agrega una cola a la lista de colas.
 */
void Broadcaster::addQueueToList(BlockingQueue &q)
{
    std::unique_lock<std::mutex> lock(mutex);
    queues.push_back(&q);
}

/*
 *  Le agrega un mensaje que indica el fin a la cola del cliente.
 *  Luego elimina una cola de la lista de colas.
 */
void Broadcaster::removeQueueFromList(BlockingQueue *q)
{
    std::unique_lock<std::mutex> lock(mutex);
    DeadDto *dto = new DeadDto();
    for (auto it = queues.begin(); it != queues.end();)
    {
        if (*it == q)
        {
            q->push(dto);
            it = queues.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

/*
 *  Vacia todas las colas que almacena la lista de colas.
 *  Luego vacia la lista de colas.
 */
void Broadcaster::deleteAllQueues()
{
    for (BlockingQueue *queue : queues)
    {
        queue->clear();
    }
    queues.clear();
}
