#ifndef ELEGIR_PARTIDA_H
#define ELEGIR_PARTIDA_H

#include <QMainWindow>

#include "client.h"

namespace Ui {
class ElegirPartida;
}

class ElegirPartida : public QMainWindow
{
    Q_OBJECT

private:
    Ui::ElegirPartida *ui;
    Client &cliente;

    // Agregamos las opciones de partida al QComboBox
    void addItems();
    uint8_t obtener_id(std::string &opcion);
    // Conectamos la señal clicked() de los botones a una ranura
    void connectEvents();
    void elegirPartida();

public:
    ElegirPartida(Client &cliente, QWidget *parent = nullptr);
    ~ElegirPartida();
};

#endif // ELEGIR_PARTIDA_H
