#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>

#include "server_aceptador.h"

class Servidor {
private:
    const std::string& servname;

public:
    explicit Servidor(const std::string& servname);

    void iniciar();
};

#endif
