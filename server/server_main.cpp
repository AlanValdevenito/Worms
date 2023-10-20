#include "server_servidor.h"

int main(int argc, const char* argv[]) {

    if (argc != 2) {
        std::cerr << "Error: Cantidad incorrecta de parametros" << std::endl;
        return 1;
    }

    const std::string servname = argv[1];

    Servidor servidor(servname);
    servidor.iniciar();

    return 0;
}
