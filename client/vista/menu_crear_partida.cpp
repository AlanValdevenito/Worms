#include "menu_crear_partida.h"
#include "ui_menu_crear_partida.h"

MenuCrearPartida::MenuCrearPartida(Client &cliente, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuCrearPartida),
    cliente(cliente)
{
    ui->setupUi(this);

    connectEvents();
}

void MenuCrearPartida::connectEvents() {
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)

    connect(ui->nuevaPartidaButton, &QPushButton::clicked, this, &MenuCrearPartida::crearPartida);

    // Utilizamos la funcion connect() de Qt para establecer una conexion entre una señal y una ranura.
    // Cuando el boton elegirPartida es clickeado se emite la señal "clicked" y se llama a la ranura MainWindow::elegirPartida.
}

void MenuCrearPartida::crearPartida() {

    std::string cantidadJugadores = (ui->jugadoresComboBox->currentText()).toStdString();
    std::string mapa = (ui->mapaComboBox->currentText()).toStdString();

    if ((cantidadJugadores != "Seleccione una opcion") && (mapa != "Seleccione una opcion")) {

        std::shared_ptr<NuevaPartida> partida = std::make_shared<NuevaPartida>(std::stoi(cantidadJugadores));
        cliente.send_queue.push(partida);

        qApp->quit();
    }
}

MenuCrearPartida::~MenuCrearPartida()
{
    delete ui;
}
