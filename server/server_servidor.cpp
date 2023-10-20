#include "server_servidor.h"

#define FINALIZAR "q"

Servidor::Servidor(const std::string& servname): servname(servname) {}

void Servidor::iniciar() {
    Socket socket(this->servname.c_str());

    Aceptador aceptador(socket);
    aceptador.start();

    std::string finalizar;
    while (std::cin >> finalizar) {

        if (finalizar == FINALIZAR) {
            break;
        }
    }

    socket.shutdown(SHUT_RDWR);
    socket.close();

    aceptador.join();
}
