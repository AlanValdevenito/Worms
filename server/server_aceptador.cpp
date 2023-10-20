#include "server_aceptador.h"

#define MENSAJE_CANTIDAD_JUGADORES 6

Aceptador::Aceptador(Socket& socket): socket(socket) {}

void Aceptador::run() {
    while (true) {

        try {
            Socket peer = this->socket.accept();

            Queue<Mensaje>* queue = new Queue<Mensaje>();
            this->outgoing_queues.agregar(queue);

            Jugador* jugador = new Jugador(std::move(peer), *queue, this->outgoing_queues);
            jugador->start();

            reap_dead();

            this->jugadores.push_back(jugador);

            imprimir_cantidad_de_jugadores();

            Mensaje cantidad_de_jugadores = {MENSAJE_CANTIDAD_JUGADORES,
                                             std::to_string(this->outgoing_queues.get_contador())};
            this->outgoing_queues.broadcast(cantidad_de_jugadores);

        } catch (const std::exception& excepcion) {
            kill_all();
            break;
        }
    }
}

void Aceptador::reap_dead() {
    this->jugadores.remove_if([](Jugador* j) {
        if (j->is_dead()) {
            j->join();
            delete j;
            return true;
        }

        return false;
    });
}

void Aceptador::kill_all() {
    for (auto& j: this->jugadores) {
        j->kill();
        j->join();
        delete j;
    }

    this->jugadores.clear();
}

void Aceptador::imprimir_cantidad_de_jugadores() {
    std::ostringstream oss;
    oss << "Jugadores " << std::to_string(this->outgoing_queues.get_contador())
        << ", esperando al resto de tus amigos..." << std::endl;
    std::cout << oss.str();
}
