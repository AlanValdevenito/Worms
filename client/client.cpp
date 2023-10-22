#include "client.h"

Client::Client(Socket &&socket) : skt(std::move(socket)), protocolo(std::ref(skt)), was_closed(false) {}

Client::~Client() {}

/*
 * Se encarga de indicarle al protocolo que debe recibir la cantidad de veces indicada por consola
 * en el comando "Read n" para luego imprimirlo por pantalla.
 */
void Client::receiveNTimes(std::string data, size_t pos)
{
    int n = std::stoi(data.substr(pos + 1));

    for (int i = 0; i < n; i++)
    {
        Dto *dto = protocolo.receive(was_closed);
        std::cout << dto->message() << std::endl;
        delete dto;
    }
}

/*
 * Cierra la conversacion con el servidor.
 */
void Client::closeEverything()
{
    skt.shutdown(2);
    skt.close();
    was_closed = true;
}

/*
 * Recibe por entrada estandar una serie de caracteres y de interpretarlos segun corresponda
 * para luego enviarselo al servidor
 */
void Client::encode(std::string data)
{
    size_t pos = data.find(' ');
    std::string first_word = data.substr(0, pos);

    if (first_word == CHAT)
        protocolo.sendChatMsj(data, was_closed);
    else if (first_word == READ)
        receiveNTimes(data, pos);
    else if (first_word == EXIT)
        closeEverything();
    else
        std::cerr << "Instruccion no identificada, ingresela nuevamente." << std::endl;
    return;
}

void Client::start()
{

    std::string data;
    while (not was_closed)
    {
        data.clear();

        std::getline(std::cin, data);

        if (data.empty())
            break;

        encode(data);

        if (was_closed)
            break;
    }
    return;
}
