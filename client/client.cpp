#include "client.h"

Client::Client(Socket &&socket) : skt(std::move(socket)), protocolo(std::ref(skt)), was_closed(false), recv_th(std::ref(protocolo), std::ref(recv_queue)), send_th(std::ref(protocolo), std::ref(send_queue)) {}

Client::~Client() {}

void Client::start()
{
    recv_th.start();
    send_th.start();

    std::shared_ptr<Dto> d = recv_queue.pop();
    id = d->get_cliente_id();
}

void Client::kill()
{
    recv_th.was_closed = true;
    
    std::shared_ptr<Dto> fin = std::make_shared<Dto>(FINALIZAR_CODE, id);
    send_queue.push(fin);

    std::shared_ptr<DeadDto> dead = std::make_shared<DeadDto>();
    send_queue.push(dead);

    while(not send_th.was_closed){std::this_thread::sleep_for(std::chrono::milliseconds((int)500));}
    skt.shutdown(2);
    skt.close();
}

void Client::servidorCerro()
{
    recv_th.was_closed = true;

    std::shared_ptr<DeadDto> dead = std::make_shared<DeadDto>();
    send_queue.push(dead);

    while(not send_th.was_closed){std::this_thread::sleep_for(std::chrono::milliseconds((int)500));}
    
    skt.shutdown(2);
    skt.close();
}

void Client::join()
{
    recv_th.join();
    send_th.join();
    return;
}
