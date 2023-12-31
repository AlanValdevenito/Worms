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

/*
 *   Agrega a todas las queues del broadcaster el Dto
 */
void Broadcaster::AddDtoToQueues(std::shared_ptr<Dto> dto)
{
    std::unique_lock<std::mutex> lock(mutex);

    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(dto);
}

/*
 *  Agrega una cola a la lista de colas.
 */
void Broadcaster::addQueueToList(Queue<std::shared_ptr<Dto>> &q, uint8_t id)
{
    std::unique_lock<std::mutex> lock(mutex);
    queues.agregar(&q, id);
}

/* Le envio a todas la queues un Dto que indica que deben cerrar*/
void Broadcaster::notificarCierre()
{
    std::shared_ptr<Dto> dto = std::make_shared<Dto>(FINALIZAR_CODE);
    std::unique_lock<std::mutex> lock(mutex);
    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(dto);
}

/*
 *  Le agrega un mensaje que indica el fin a la cola del cliente.
 *  Luego elimina una cola de la lista de colas.
 */
void Broadcaster::removeQueueFromList(Queue<std::shared_ptr<Dto>> *q)
{
    std::shared_ptr<DeadDto> dto = std::make_shared<DeadDto>();
    q->push(dto); // cierro el hilo sender del cliente
    // queues.remover(q);
}

void Broadcaster::removeQueueWithId(uint8_t id)
{
    Queue<std::shared_ptr<Dto>> *q = queues.remover(id);
    std::shared_ptr<DeadDto> dto = std::make_shared<DeadDto>();
    q->push(dto);
}

/*
 *  Vacia todas las colas que almacena la lista de colas.
 *  Luego vacia la lista de colas.
 */
void Broadcaster::deleteAllQueues()
{

    std::shared_ptr<DeadDto> dto = std::make_shared<DeadDto>();
    for (Queue<std::shared_ptr<Dto>> *queue : queues.listado()) // le envio al sender que murio
        queue->push(dto);

    queues.removeAllQueues();
}
