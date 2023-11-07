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
void Broadcaster::addQueueToList(Queue<std::shared_ptr<Dto>> &q, uint8_t id)
{
    std::unique_lock<std::mutex> lock(mutex);
    queues.agregar(&q, id);
}


void Broadcaster::notificarCierre(std::shared_ptr<Dto> dto)
{
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
    q->push(dto);
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
    // std::shared_ptr<Dto> fin = std::make_shared<Dto>(FINALIZAR_CODE);
    // notificarCierre(fin);
    

    int i = 0;

    while(i <1000){i++;}

    std::shared_ptr<DeadDto> dto = std::make_shared<DeadDto>();
    for (Queue<std::shared_ptr<Dto>> *queue : queues.listado())// le envio al sender que murio 
        queue->push(dto);
    

    queues.removeAllQueues();  
}
