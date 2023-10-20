#include "client_cliente.h"

int main(int argc, const char* argv[]) {

    if (argc != 3) {
        std::cerr << "Error: Cantidad incorrecta de parametros" << std::endl;
        return 1;
    }

    const std::string hostname = argv[1];
    const std::string servname = argv[2];

    Socket socket(hostname.c_str(), servname.c_str());
    Cliente cliente(std::move(socket));

    cliente.conectarse();
    return 0;
}
