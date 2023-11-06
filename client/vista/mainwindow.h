#ifndef VENTANA_H
#define VENTANA_H

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>

#include "client.h"

// La clase MainWindow es la ventana principal de la aplicacion y hereda de QMainWindow

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    Client &cliente;

    // Agregamos las opciones de partida al QComboBox
    void addItems();
    uint8_t obtener_id(std::string &opcion);
    // Conectamos la señal clicked() de los botones a una ranura
    void connectEvents();
    void elegirPartida();
    void nuevaPartida();

public:
    // Metodo constructor donde se configura la interfaz de usuario creada en QtDesigner
    MainWindow(Client &cliente, QWidget *parent = nullptr);
    ~MainWindow();
};

#endif
