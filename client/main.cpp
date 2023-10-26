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


        // std::string data;

        // while (data != "exit")
        // {
        //     // queue.pop();
        //     data.clear();

        //     std::getline(std::cin, data);

        //     if (data.empty())
        //         break;
        // }
        //Dto *d = new Dto();
        //client.send_queue.push(d);
        // client.recv_queue

        vista.iniciar();

        client.join();

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
