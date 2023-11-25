#ifndef CREAR_PARTIDA_H
#define CREAR_PARTIDA_H

#include <QMainWindow>

#include "client.h"

namespace Ui {
class CrearPartida;
}

class CrearPartida : public QMainWindow
{
    Q_OBJECT

private:
    Ui::CrearPartida *ui;
    Client &cliente;

    // Conectamos la señal clicked() de los botones a una ranura
    void connectEvents();
    void nuevaPartida();

public:
    CrearPartida(Client &cliente, QWidget *parent = nullptr);
    ~CrearPartida();

};

#endif // CREAR_PARTIDA_H
