#include <cstdint>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>

#include <netinet/in.h>

#include "socket.h"
#include "server.h"

const int EXITO_PROGRAMA = 0;
const int ERROR_PROGRAMA = 1;
const uint8_t ERROR = 1;

int main(int argc, char *argv[])
{
    try
    {
        int ret = -1;

        const char *servname = NULL;

        if (argc == 2)
        {
            servname = argv[1];
        }
        else
        {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return ret;
        }
        Server srv(servname);
        srv.main();

        ret = EXITO_PROGRAMA;
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
