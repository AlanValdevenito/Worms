#ifndef MENU_CREAR_PARTIDA_H
#define MENU_CREAR_PARTIDA_H

#include <QMainWindow>

#include "client.h"
#include "menu_principal.h"

namespace Ui {
class MenuCrearPartida;
}

class MenuCrearPartida : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MenuCrearPartida *ui;
    Client &cliente;

    void connectEvents();
    void crearPartida();
    void menuPrincipal();

public:
    MenuCrearPartida(Client &cliente, QWidget *parent = nullptr);
    ~MenuCrearPartida();

};

#endif // MENU_CREAR_PARTIDA_H
