#include "server_client.h"

ServerClient::ServerClient(Socket &&socket,
                           Broadcaster &b,
                           BlockingQueue &q) : common_queue(q), skt(std::move(socket)),
                                               broadcaster(b),
                                               serverproto(std::ref(skt)),
                                               recv_th(std::ref(serverproto), std::ref(common_queue), std::ref(b)),
                                               send_th(std::ref(serverproto), std::ref(sender_queue)) {}

ServerClient::~ServerClient() {}

void ServerClient::addMapToQueue()
{
}

void ServerClient::start()
{
    addMapToQueue();
    is_alive = keep_talking = true;

    recv_th.start();
    send_th.start();
}

bool ServerClient::is_dead() { return not is_alive; }

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
