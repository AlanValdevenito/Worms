#ifndef VENTANA_MENU_H
#define VENTANA_MENU_H

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>

#include "client.h"
#include "elegir_partida.h"
#include "crear_partida.h"

// La clase MainWindow es la ventana principal de la aplicacion y hereda de QMainWindow

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MenuWindow: public QMainWindow {
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    Client &cliente;

    // Conectamos la señal clicked() de los botones a una ranura
    void connectEvents();
    void elegirPartida();
    void nuevaPartida();

public:
    // Metodo constructor donde se configura la interfaz de usuario creada en QtDesigner
    MenuWindow(Client &cliente, QWidget *parent = nullptr);
    ~MenuWindow();
};

#endif