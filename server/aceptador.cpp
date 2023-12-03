#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "broadcaster.h"
#include "socket.h"
#include "thread.h"
#include "server_client.h"
#include "server_protocol.h"
#include "lobby.h"

class Aceptador : public Thread
{
private:
    Socket &skt;
    Lobby lobby;

public:
    void run() override
    {
        // crear juego
        while (_keep_running)
        {
            Socket *peer = (Socket *)skt.accept();
            lobby.newClient(peer);

            // mandar mapa a la sender_queue del nuevo cliente
        }
        kill_all();
    }

    void kill_all()
    {
        lobby.kill();
    }

    void stop_running() { _keep_running = false; }

    explicit Aceptador(Socket &skt) : skt(skt) {}
};
