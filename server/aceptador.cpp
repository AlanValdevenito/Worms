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

struct Aceptador : public Thread
{
private:
    std::list<ServerClient *> clients; // no es recurso compartido
    Socket &skt;
    Broadcaster broadcaster;
    BlockingQueue common_queue;

public:
    void run() override
    {
        while (_keep_running)
        {
            Socket peer = skt.accept();

            ServerClient *th = new ServerClient(std::move(peer), std::ref(broadcaster), std::ref(common_queue));
            th->start();

            reap_dead();

            clients.push_back(th);
            // broadcaster.addQueueToList(std::ref(th->sender_queue));
            // broadcaster.addMessageToQueues();
        }
        kill_all();
    }

    void kill_all()
    {
        for (auto &c : clients)
        {
            c->kill();
            c->join();
            delete c;
        }
        broadcaster.deleteAllQueues();
        clients.clear();
    }

    void stop_running() { _keep_running = false; }

    void reap_dead()
    {
        bool was_removed = false;
        BlockingQueue *client_queue;

        clients.remove_if([&](ServerClient *c)
                          {
            if (c->is_dead()) {
                c->join();
                was_removed = true;
                client_queue = &c->sender_queue;  // obtengo el puntero de la queue para eliminarlo despues
                delete c;
                return true;
            }
            return false; });
        if (was_removed)
            broadcaster.removeQueueFromList(client_queue);
    }

    explicit Aceptador(Socket &skt) : skt(skt) {}
};
