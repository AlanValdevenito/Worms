#ifndef MENU_FINALIZAR_H
#define MENU_FINALIZAR_H

#include <QMainWindow>
#include <string>

#include "client.h"

namespace Ui {
class MenuFinalizar;
}

class MenuFinalizar : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MenuFinalizar *ui;
    Client &cliente;
    int resultado;

    void connectEvents();
    void salir();
    void update();

public:
    MenuFinalizar(Client &cliente, int resultado = 0, QWidget *parent = nullptr);
    ~MenuFinalizar();
};

#endif // MENU_FINALIZAR_H
