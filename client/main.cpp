#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <vector>

#include <netinet/in.h>

const int EXITO_PROGRAMA = 0;
const int ERROR_PROGRAMA = 1;
const uint8_t ERROR = 1;

#include "client.h"
#include "socket.h"
#include "client_vista.h"
#include "dto.h"
#include "mover.h"

void elegirPartida(Client &client);

int main(int argc, char *argv[])
{

    try
    {
        int ret = -1;
        const char *host = NULL;
        const char *servname = NULL;

        if (argc == 3)
        {
            host = argv[1];
            servname = argv[2];
        }
        else
        {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return ret;
        }

        Socket client_socket(host, servname);
        Client client(std::move(client_socket));

        Vista vista(client);

        client.start();
        // elegirPartida(std::ref(client));

        vista.iniciar();

        // Dto* d = new MoverADerecha();
        // client.send_queue.push(d);

        client.join(); // Se queda en join y no termina

        ret = 0;
        return ret;
    }
    catch (const std::exception &err)
    {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    }
    catch (...)
    {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}

void elegirPartida(Client &client)
{
    // ListaDePartidas *l = (ListaDePartidas *)client.recv_queue.pop();

    // std::list<uint8_t> lista = l->return_list();
    // for (uint8_t o : lista)
    // {
    //     printf("opcion: %u \n", o); // ver de hacer un MAP
    //     // que ListaDePartidas sea un map y el seleccionar sea pasandole la key
    // }

    // uint8_t s = 2;
    // ListaDePartidas *seleccion = new ListaDePartidas(s);
    // client.send_queue.push(seleccion);
}
