#include "crear_partida.h"
#include "ui_crear_partida.h"

CrearPartida::CrearPartida(Client &cliente, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CrearPartida),
    cliente(cliente)
{
    ui->setupUi(this);
    
    connectEvents();

    cliente.recv_queue.pop();
}

void CrearPartida::connectEvents() {
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)

    connect(ui->nuevaPartidaButton, &QPushButton::clicked, this, &CrearPartida::nuevaPartida);

    // Utilizamos la funcion connect() de Qt para establecer una conexion entre una señal y una ranura.
    // Cuando el boton elegirPartida es clickeado se emite la señal "clicked" y se llama a la ranura MainWindow::elegirPartida.
}

void CrearPartida::nuevaPartida() {
    std::string cantidadSeleccionada = (ui->jugadoresComboBox->currentText()).toStdString();
    std::string mapaSeleccionado = (ui->mapaComboBox->currentText()).toStdString();

    if ((cantidadSeleccionada != "Cantidad de jugadores") && (mapaSeleccionado != "Mapa")) {

        std::shared_ptr<NuevaPartida> partida = std::make_shared<NuevaPartida>(std::stoi(cantidadSeleccionada));
        cliente.send_queue.push(partida);

        qApp->quit();
    }
}

CrearPartida::~CrearPartida()
{
    delete ui;
}
