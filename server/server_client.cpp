#include "server_client.h"

ServerClient::ServerClient(Socket &&socket, Queue<std::shared_ptr<Dto>> *q, uint8_t id) : id(id),
                                                                                          receiver_queue(q), skt(std::move(socket)), serverproto(std::ref(skt)),
                                                                                          recv_th(std::ref(serverproto), receiver_queue), send_th(std::ref(serverproto), std::ref(sender_queue))
{
    std::shared_ptr<Dto> d = std::make_shared<ClienteId>(id); // agrego el id del cliente a la cola de envios
    sender_queue.push(d);
}

ServerClient::~ServerClient() {}

// cambio la queue que tenia del lobby por la de la partida seleccionada
void ServerClient::changeReceiverQueue(Queue<std::shared_ptr<Dto>> *q)
{
    receiver_queue = q;
    recv_th.changeReceiverQueue(q);
}

void ServerClient::start()
{
    is_alive = keep_talking = true;

    recv_th.start();
    send_th.start();
}

bool ServerClient::is_dead()
{
    return not is_alive;
}

void ServerClient::kill()
{
    keep_talking = false;

    if (not recv_th.was_closed)
    {
        skt.shutdown(2);
        skt.close();
    }
}

void ServerClient::join()
{
    recv_th.join();
    send_th.join();
}
