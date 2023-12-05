#ifndef VENTANA_MENU_H
#define VENTANA_MENU_H

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>

#include "client.h"
#include "menu_partidas.h"
#include "menu_crear_partida.h"

// La clase MainWindow es la ventana principal de la aplicacion y hereda de QMainWindow

QT_BEGIN_NAMESPACE
namespace Ui { class MenuPrincipal; }
QT_END_NAMESPACE

class MenuPrincipal: public QMainWindow {
    Q_OBJECT

private:
    Ui::MenuPrincipal *ui;
    Client &cliente;
    std::list<uint8_t> partidas;

    // Conectamos la señal clicked() de los botones a una ranura
    void connectEvents();
    void menuPartidas();
    void menuCrearPartida();

public:
    // Metodo constructor donde se configura la interfaz de usuario creada en QtDesigner
    MenuPrincipal(Client &cliente, QWidget *parent = nullptr);
    ~MenuPrincipal();
};

#endif
