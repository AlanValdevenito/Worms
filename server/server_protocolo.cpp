#include "server_protocolo.h"

#define MENSAJE_CANTIDAD_JUGADORES 6
#define MENSAJE_CHAT 9

ProtocoloServidor::ProtocoloServidor(Socket& socket): socket(socket) {}

Mensaje ProtocoloServidor::esperar_mensaje_de_chat(bool* was_closed) {
    uint8_t byteTipo;
    socket.recvall(&byteTipo, sizeof(byteTipo), was_closed);
    int tipo = static_cast<int>(byteTipo);

    if (*was_closed) {
        return {-1, ""};
    }

    uint16_t largo_net;
    socket.recvall(&largo_net, sizeof(largo_net), was_closed);
    int largo = ntohs(largo_net);

    std::vector<char> buffer_mensaje(largo, 0);
    socket.recvall(buffer_mensaje.data(), buffer_mensaje.size(), was_closed);
    std::string msg(buffer_mensaje.begin(), buffer_mensaje.end());

    return {tipo, msg};
}

void ProtocoloServidor::enviar_cantidad_de_jugadores(const Mensaje& mensaje) {
    bool was_closed = false;
    std::vector<uint8_t> bytes;

    uint8_t accion = static_cast<uint8_t>(MENSAJE_CANTIDAD_JUGADORES);
    uint8_t cantidad = static_cast<uint8_t>(std::stoul(mensaje.msg));

    bytes.resize(sizeof(accion) + sizeof(cantidad));
    memcpy(bytes.data(), &accion, sizeof(accion));
    memcpy(bytes.data() + sizeof(accion), &cantidad, sizeof(cantidad));

    socket.sendall(bytes.data(), bytes.size(), &was_closed);
}

void ProtocoloServidor::enviar_mensaje_de_chat(const Mensaje& mensaje) {
    bool was_closed = false;
    std::vector<uint8_t> bytes;

    uint8_t accion = static_cast<uint8_t>(MENSAJE_CHAT);

    uint16_t longitud = static_cast<uint16_t>(mensaje.msg.size());
    uint16_t longitud_net = htons(longitud);

    bytes.resize(sizeof(accion) + sizeof(longitud_net) + mensaje.msg.size());
    memcpy(bytes.data(), &accion, sizeof(accion));
    memcpy(bytes.data() + sizeof(accion), &longitud_net, sizeof(longitud_net));
    memcpy(bytes.data() + sizeof(accion) + sizeof(longitud_net), mensaje.msg.c_str(),
           mensaje.msg.size());

    socket.sendall(bytes.data(), bytes.size(), &was_closed);
}
