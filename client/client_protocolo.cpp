#include "client_protocolo.h"

#define SEND 5

#define MENSAJE_CANTIDAD_JUGADORES 6
#define MENSAJE_CHAT 9

ProtocoloCliente::ProtocoloCliente(Socket&& socket): socket(std::move(socket)) {}

void ProtocoloCliente::send(const Mensaje& mensaje) {
    bool was_closed = false;
    std::vector<uint8_t> bytes;

    uint8_t accion = static_cast<uint8_t>(SEND);

    uint16_t longitud = static_cast<uint16_t>(mensaje.msg.size());
    uint16_t longitud_net = htons(longitud);

    bytes.resize(sizeof(accion) + sizeof(longitud_net) + mensaje.msg.size());
    memcpy(bytes.data(), &accion, sizeof(accion));
    memcpy(bytes.data() + sizeof(accion), &longitud_net, sizeof(longitud_net));
    memcpy(bytes.data() + sizeof(accion) + sizeof(longitud_net), mensaje.msg.c_str(),
           mensaje.msg.size());

    socket.sendall(bytes.data(), bytes.size(), &was_closed);
}

Mensaje ProtocoloCliente::recv() {
    Mensaje mensaje;

    bool was_closed = false;

    uint8_t byteTipo;
    socket.recvall(&byteTipo, sizeof(byteTipo), &was_closed);
    mensaje.tipo = static_cast<int>(byteTipo);

    if (mensaje.tipo == MENSAJE_CANTIDAD_JUGADORES) {
        uint8_t byteCantidad;
        socket.recvall(&byteCantidad, sizeof(byteCantidad), &was_closed);
        mensaje.msg = std::to_string(static_cast<int>(byteCantidad));

    } else if (mensaje.tipo == MENSAJE_CHAT) {
        uint16_t byteLargo;
        socket.recvall(&byteLargo, sizeof(byteLargo), &was_closed);
        int largo = ntohs(byteLargo);

        std::vector<char> buffer_mensaje(largo, 0);
        socket.recvall(buffer_mensaje.data(), buffer_mensaje.size(), &was_closed);
        std::string msg(buffer_mensaje.begin(), buffer_mensaje.end());

        mensaje.msg = msg;
    }

    return mensaje;
}
