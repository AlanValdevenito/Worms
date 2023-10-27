#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "aceptador.cpp"
#include "socket.h"
#include "dto.h"
#include "server_client.h"

class Server
{
public:
    explicit Server(const char *servname);
    ~Server();
    void main();

private:
    Socket aceptador;
    const char *servername;
    Aceptador accept_th;
};
#endif
