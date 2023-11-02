#include "broadcaster.h"

/*
 *   Crea un Dto que indica que la partida comienza y  se lo agrega a todas las colas
 */
void Broadcaster::addMessageToQueues()
{
    std::unique_lock<std::mutex> lock(mutex);
    std::shared_ptr<Dto> d = std::make_shared<Dto>(INICIAR_PARIDA);
    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(d);

}

void Broadcaster::AddGusanoToQueues(std::shared_ptr<Gusano> g)
{
    std::unique_lock<std::mutex> lock(mutex);
    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(g);
}


void Broadcaster::AddGusanosToQueues(std::shared_ptr<Gusanos> gs)
{
    std::unique_lock<std::mutex> lock(mutex);

    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(gs);
}


void Broadcaster::AddVigasToQueues(std::shared_ptr<Vigas> vs)
{
    std::unique_lock<std::mutex> lock(mutex);

    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(vs);
}


/*
 *  Agrega una cola a la lista de colas.
 */
void Broadcaster::addQueueToList(Queue<std::shared_ptr<Dto>> &q)
{
    std::unique_lock<std::mutex> lock(mutex);
    queues.agregar(&q);
}

/*
 *  Le agrega un mensaje que indica el fin a la cola del cliente.
 *  Luego elimina una cola de la lista de colas.
 */
void Broadcaster::removeQueueFromList(Queue<std::shared_ptr<Dto>> *q)
{
    std::shared_ptr<DeadDto> dto = std::make_shared<DeadDto>();
    q->push(dto);
    queues.remover(q);
}

/*
 *  Vacia todas las colas que almacena la lista de colas.
 *  Luego vacia la lista de colas.
 */
void Broadcaster::deleteAllQueues()
{
    for (Queue<std::shared_ptr<Dto>> *queue : queues.listado())
    {
        // queue->close(true);
        queue->close();
        queues.remover(queue);
    }
}
