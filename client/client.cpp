#include "client.h"

Client::Client(Socket &&socket) : skt(std::move(socket)), protocolo(std::ref(skt)), was_closed(false), recv_th(std::ref(protocolo), std::ref(recv_queue)), send_th(std::ref(protocolo), std::ref(send_queue), std::ref(broadcaster)) {}

Client::~Client() {}

void Client::start()
{
    broadcaster.addQueueToList(recv_queue);
    recv_th.start();
    send_th.start();
}

void Client::join()
{
    recv_th.join();
    send_th.join();
}
