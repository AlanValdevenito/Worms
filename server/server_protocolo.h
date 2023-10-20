#ifndef PROTOCOLO_SERVIDOR_H
#define PROTOCOLO_SERVIDOR_H

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

class ProtocoloServidor {
private:
    Socket& socket;

public:
    explicit ProtocoloServidor(Socket& socket);

    Mensaje esperar_mensaje_de_chat(bool* was_closed);
    void enviar_cantidad_de_jugadores(const Mensaje& mensaje);
    void enviar_mensaje_de_chat(const Mensaje& mensaje);
};

#endif
