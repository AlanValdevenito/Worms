#ifndef VENTANA_MENU_H
#define VENTANA_MENU_H

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>

#include "client.h"
#include "menu_partidas.h"

// La clase MainWindow es la ventana principal de la aplicacion y hereda de QMainWindow

QT_BEGIN_NAMESPACE
namespace Ui { class MenuPrincipal; }
QT_END_NAMESPACE

class MenuPrincipal: public QMainWindow {
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MenuPrincipal *ui;
    Client &cliente;

    // Conectamos la señal clicked() de los botones a una ranura
    void connectEvents();
    void menuPartidas();
    void menuOpciones();

public:
    // Metodo constructor donde se configura la interfaz de usuario creada en QtDesigner
    MenuPrincipal(Client &cliente, QWidget *parent = nullptr);
    ~MenuPrincipal();
};

#endif
