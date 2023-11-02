#include "broadcaster.h"

/*
 *   Crea un Dto y agrega a todas las colas una instancia nueva del dto
 *   Luego lo elimina del HEAP
 */
void Broadcaster::addMessageToQueues()
{
    std::unique_lock<std::mutex> lock(mutex);
    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
    {
        std::cout << "agrego msj a las queues msj \n";
        std::shared_ptr<Dto> d = std::make_shared<Dto>(INICIAR_PARIDA);
        q->push(d);
    }

    // std::cout << dto->message() << std::endl;

    // delete dto;
}

void Broadcaster::AddGusanoToQueues2(std::shared_ptr<Gusano> g)
{
    std::unique_lock<std::mutex> lock(mutex);
    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(g);
}

// void Broadcaster::AddGusanoToQueues(Gusano *g)
// {
//     std::unique_lock<std::mutex> lock(mutex);
//     for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
//     {
//         std::shared_ptr<Dto> d = new Gusano(g->get_id(), g->x_pos(), g->y_pos());
//         q->push(d);
//     }
//     // delete g;
// }

void Broadcaster::AddGusanosToQueues2(std::shared_ptr<Gusanos> gs)
{
    std::unique_lock<std::mutex> lock(mutex);

    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(gs);
}

// void Broadcaster::AddGusanosToQueues(Gusanos *gs)
// {
//     std::unique_lock<std::mutex> lock(mutex);

//     std::list<Gusano *> gusanos = gs->return_gusanos_list();

//     std::list<Gusano *> lista;
//     for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
//     {
//         for (Gusano *g : gusanos)
//         {
//             Gusano *worm = new Gusano(g->get_id(), g->x_pos(), g->y_pos());
//             lista.push_back(worm);
//         }

//         std::shared_ptr<Dto> d = new Gusanos(lista);
//         q->push(d);

//         lista.clear();
//     }
//     // delete gs;
// }

void Broadcaster::AddVigasToQueues2(std::shared_ptr<Vigas> vs)
{
    std::unique_lock<std::mutex> lock(mutex);

    for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
        q->push(vs);
}

// void Broadcaster::AddVigasToQueues(Vigas *vs)
// {
//     std::unique_lock<std::mutex> lock(mutex);

//     std::list<Viga *> vigas = vs->return_vigas_list();

//     std::list<Viga *> lista;
//     for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
//     {
//         for (Viga *v : vigas)
//         {
//             Viga *viga = new Viga(v->x_pos(), v->y_pos(), v->return_ancho(), v->return_alto());
//             lista.push_back(viga);
//         }

//         std::shared_ptr<Dto> d = new Vigas(lista);
//         q->push(d);

//         lista.clear();
//     }

//     // delete vs;
// }

/*
 *   Por cada cola, crea una nueva instancia del Dto recibido, y se lo agrega a todas.
 *   Luego lo elimina el Dto original del HEAP
 *   (Se que solo llegaran a este metodos mensajes de tipo chat)
 */
// void Broadcaster::addMessageToQueues(std::shared_ptr<Dto> dto)
// {
//     std::unique_lock<std::mutex> lock(mutex);
//     for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
//     {
//         std::shared_ptr<Dto> d = new Dto();
//         q->push(d);
//     }
//     // delete dto;
// }

// void Broadcaster::addVigaToQueues(std::shared_ptr<Dto> dto)
// {
//     std::unique_lock<std::mutex> lock(mutex);
//     for (Queue<std::shared_ptr<Dto>> *q : queues.listado())
//     {
//         std::shared_ptr<Dto> d = new Viga(dto->x_pos(), dto->y_pos(), dto->return_ancho(), dto->return_alto());
//         q->push(d);
//     }
//     // delete dto;
// }

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
    // std::unique_lock<std::mutex> lock(mutex);
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
