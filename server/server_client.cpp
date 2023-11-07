#include "server_client.h"

ServerClient::ServerClient(Socket &&socket, Queue<std::shared_ptr<Dto>> *q, uint8_t id) : id(id),
                                                                                          receiver_queue(q), skt(std::move(socket)), serverproto(std::ref(skt)),
                                                                                          recv_th(std::ref(serverproto), receiver_queue), send_th(std::ref(serverproto), std::ref(sender_queue))
// ServerClient::ServerClient(Socket &&socket, Queue<std::shared_ptr<Dto>> &lq, Queue<std::shared_ptr<Dto>> &q, uint8_t id) : id(id),
//    common_queue(q), skt(std::move(socket)), lobby_queue(lq), serverproto(std::ref(skt)),
//    recv_th(std::ref(serverproto), std::ref(common_queue), std::ref(lq)), send_th(std::ref(serverproto), std::ref(sender_queue))
{
    std::shared_ptr<Dto> d = std::make_shared<ClienteId>(id); // agrego el id del cliente a la cola de envios
    sender_queue.push(d);
}

ServerClient::~ServerClient() {}

// le tengo que poner friend al metodo para la partida?
// cambio la queue que tenia del lobby por la de la partida seleccionada
void ServerClient::changeReceiverQueue(Queue<std::shared_ptr<Dto>> *q)
{
    std::cout<<"queue antes: " << receiver_queue<< std::endl;
    receiver_queue = q;
    std::cout<<"queue despues: " << receiver_queue<< std::endl;
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
