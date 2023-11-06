#include "client_menu.h"
#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QMainWindow>

Menu::Menu(Client &cliente): cliente(cliente) {}

int Menu::iniciar(int argc, char* argv[]) {

    // Inicializamos la aplicacion Qt
    // Es la clase que contiene el loop principal
    // Se encarga de gestionar todos los eventos ocurridos en la aplicacion.
    // Este monitoreo de eventos lo realiza en un bucle conocido como loop de eventos.
    QApplication app(argc, argv);

    // Creamos una ventana
    MainWindow w(this->cliente);

    // Mostramos la ventana
    w.show();
    
    // Arranca el loop de la UI. Ejecutamos la aplicacion.
    return app.exec();
}