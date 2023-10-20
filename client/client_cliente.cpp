#include "client_cliente.h"

#define CHAT "Chat"
#define READ "Read"
#define EXIT "Exit"

#define SEND 5

#define MENSAJE_CANTIDAD_JUGADORES 6
#define MENSAJE_CHAT 9

Cliente::Cliente(Socket&& socket): protocolo(std::move(socket)) {}

void Cliente::conectarse() {
    std::string accion;

    while (std::cin >> accion) {

        if (accion == CHAT) {
            Mensaje mensaje = parsear();
            send(mensaje);

        } else if (accion == READ) {
            int cantidad;
            std::cin >> cantidad;

            recv(cantidad);

        } else if (accion == EXIT) {
            break;
        }
    }
}

void Cliente::send(const Mensaje& mensaje) { this->protocolo.send(mensaje); }

void Cliente::recv(const int& cantidad) {

    for (int i = 0; i < cantidad; i++) {
        Mensaje mensaje_recibido = this->protocolo.recv();
        imprimir(mensaje_recibido);
    }
}

void Cliente::imprimir(const Mensaje& mensaje) {

    if (mensaje.tipo == MENSAJE_CANTIDAD_JUGADORES) {
        std::cout << "Jugadores " + mensaje.msg + ", esperando al resto de tus amigos..."
                  << std::endl;

    } else if (mensaje.tipo == MENSAJE_CHAT) {
        std::cout << mensaje.msg << std::endl;
    }
}

Mensaje Cliente::parsear() {
    std::string primer_palabra;
    std::cin >> primer_palabra;

    std::string resto;
    std::getline(std::cin, resto);

    std::string msg = primer_palabra + resto;
    return {SEND, msg};
}
