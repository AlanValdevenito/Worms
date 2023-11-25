#include "elegir_partida.h"
#include "ui_elegir_partida.h"

ElegirPartida::ElegirPartida(Client &cliente, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ElegirPartida),
    cliente(cliente)
{
    ui->setupUi(this);
    addItems();
    connectEvents();
}

void ElegirPartida::addItems() {
    std::shared_ptr<ListaDePartidas> l = std::dynamic_pointer_cast<ListaDePartidas>(cliente.recv_queue.pop());

    std::list<uint8_t> lista = l->return_list();

    for (uint8_t id : lista) {
        QString partida = QString::fromStdString("Partida " + std::to_string((int) id));
        ui->partidasComboBox->addItem(partida);
    }

}

void ElegirPartida::connectEvents() {
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)

    connect(ui->elegirPartidaButton, &QPushButton::clicked, this, &ElegirPartida::elegirPartida);

    // Utilizamos la funcion connect() de Qt para establecer una conexion entre una señal y una ranura.
    // Cuando el boton elegirPartida es clickeado se emite la señal "clicked" y se llama a la ranura MainWindow::elegirPartida.
}

uint8_t ElegirPartida::obtener_id(std::string &opcion) {
    std::istringstream ss(opcion);
    std::string texto;
    int numero;

    ss >> texto >> numero;

    return static_cast<uint8_t>(numero);
}

void ElegirPartida::elegirPartida() {
    std::string opcionSeleccionada = (ui->partidasComboBox->currentText()).toStdString();

    if (opcionSeleccionada != "Partidas") {
        uint8_t id = obtener_id(opcionSeleccionada);

        std::shared_ptr<ListaDePartidas> seleccion = std::make_shared<ListaDePartidas>(this->cliente.id, id);
    	cliente.send_queue.push(seleccion);
        
        qApp->quit();
    }

}

ElegirPartida::~ElegirPartida()
{
    delete ui;
}
