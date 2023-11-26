#ifndef ELEGIR_PARTIDA_H
#define ELEGIR_PARTIDA_H

#include <QMainWindow>

#include "client.h"
#include "menu_crear_partida.h"

namespace Ui {
class MenuPartidas;
}

class MenuPartidas : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MenuPartidas *ui;
    Client &cliente;

    std::string partidaSeleccionada;

    // Agregamos las opciones de partida al QComboBox
    void addItems();
    uint8_t obtener_id(std::string &opcion);
    // Conectamos la señal clicked() de los botones a una ranura
    void connectEvents();
    void seleccionarPartida();
    void elegirPartida();
    void menuCrearPartida();

public:
    MenuPartidas(Client &cliente, QWidget *parent = nullptr);
    ~MenuPartidas();
};

#endif // ELEGIR_PARTIDA_H
