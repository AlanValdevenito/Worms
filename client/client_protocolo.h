#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "common_socket.h"

struct Mensaje {
    // cppcheck-suppress unusedStructMember
    int tipo;
    std::string msg;
};

class ProtocoloCliente {
private:
    Socket socket;

public:
    explicit ProtocoloCliente(Socket&& socket);

    void send(const Mensaje& mensaje);
    Mensaje recv();
};

#endif
