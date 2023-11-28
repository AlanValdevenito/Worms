#include "client_vista.h"

Vista::Vista(Client &cliente) : cliente(cliente), menu(cliente), partida(cliente), finalizar(cliente) {}

int Vista::iniciar(int argc, char* argv[])
{
    /******************** MENU DE PARTIDAS ********************/

    menu.iniciar(argc, argv);

    /******************** PARTIDA BLOQUEADA HASTA QUE SE CONECTEN TODOS LOS CLIENTES ********************/

    // Como en la partida debemos hacer pop() de lo que recibe el cliente desde el servidor luego de iniciar SDL, nos
    // puede pasar de quedarnos bloqueados y esto ocasionaria que la ventana de SDL deje de responder

    // Para solucionar esto, antes de iniciar la partida lo primero que hacemos es un pop() para bloquearnos antes de iniciar SDL. Lo
    // que esperamos recibir es una señal avisandonos que todos los jugadores se conectaron

    // Luego de que todos los jugadores se conectan, el servidor le envia a todos los clientes el mapa (vigas) y los worms. Por lo tanto
    // cuando se quiera hacer pop() de estas cosas ya no nos quedaremos bloqueados y no se frenara la ejecucion de SDL

    std::cout << "Esperando la señal para iniciar la partida" << std::endl;
    cliente.recv_queue.pop();
    std::cout << "Inicia la partida" << std::endl;

    /******************** PARTIDA ********************/

    int resultado = partida.iniciar();

    /******************** FINALIZACION DE LA PARTIDA ********************/

    finalizar.iniciar(argc, argv, resultado);

    return 0;
}
