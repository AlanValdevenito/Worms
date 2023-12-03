#include "client_finalizar.h"
#include "menu_finalizar.h"

#include <QApplication>
#include <QLabel>
#include <QMainWindow>

Finalizar::Finalizar(Client &cliente): cliente(cliente) {}

int Finalizar::iniciar(int argc, char* argv[], int resultado) {

    // Inicializamos la aplicacion Qt
    // Es la clase que contiene el loop principal
    // Se encarga de gestionar todos los eventos ocurridos en la aplicacion.
    // Este monitoreo de eventos lo realiza en un bucle conocido como loop de eventos.
    QApplication app(argc, argv);

    // Creamos una ventana
    MenuFinalizar w(this->cliente, resultado);

    // Mostramos la ventana
    w.show();
    
    // Arranca el loop de la UI. Ejecutamos la aplicacion.
    return app.exec();
}