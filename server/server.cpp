#include "server.h"

Server::Server(const char *servname) : aceptador(servname), servername(servname), accept_th(std::ref(aceptador)) {}

Server::~Server() {}

void Server::main()
{

    accept_th.start();
    char c;
    while ((c = std::cin.get()) != 'q')
    {
    }

    accept_th.kill_all();

    aceptador.shutdown(2);
    aceptador.close();
    accept_th.join();
}
