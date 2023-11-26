#include "menu_partidas.h"
#include "ui_menu_partidas.h"

#include <QPushButton>

MenuPartidas::MenuPartidas(Client &cliente, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuPartidas),
    cliente(cliente),
    partidaSeleccionada("")
{
    ui->setupUi(this);
    addItems();
    connectEvents();
}

void MenuPartidas::addItems() {
    std::shared_ptr<ListaDePartidas> l = std::dynamic_pointer_cast<ListaDePartidas>(cliente.recv_queue.pop());

    std::list<uint8_t> lista = l->return_list();

    QVBoxLayout *layout = new QVBoxLayout();
    for (uint8_t id : lista) {
        QString partida = QString::fromStdString("Partida " + std::to_string((int) id));

        QPushButton *partidaButton = new QPushButton(partida, this);
        partidaButton->setStyleSheet("QPushButton {" 
                                     "  border: none;"
                                     "  border-top: 1px solid black;"
                                     "  border-bottom: 1px solid black;"
                                     "  text-align: left;"
                                     "  padding-left: 5px;"
                                     "  background-color: transparent;" 
                                     "}"
                                     "QPushButton:pressed {"
                                     "  background-color: gray;"
                                     "}");

        layout->addWidget(partidaButton);
    }

    layout->addStretch(1);
    ui->scrollContentsPartida->setLayout(layout);

}

void MenuPartidas::connectEvents() {
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)

    connect(ui->elegirPartidaButton, &QPushButton::clicked, this, &MenuPartidas::elegirPartida);
    connect(ui->crearPartidaButton, &QPushButton::clicked, this, &MenuPartidas::menuCrearPartida);

    for (QObject *child: ui->scrollContentsPartida->children()) {
        QPushButton *partidaButton = qobject_cast<QPushButton*>(child);

        if (partidaButton) {
            connect(partidaButton, &QPushButton::clicked, this, &MenuPartidas::seleccionarPartida);
        }
    }

    // Utilizamos la funcion connect() de Qt para establecer una conexion entre una señal y una ranura.
    // Cuando el boton elegirPartida es clickeado se emite la señal "clicked" y se llama a la ranura MainWindow::elegirPartida.
}

uint8_t MenuPartidas::obtener_id(std::string &opcion) {
    std::istringstream ss(opcion);
    std::string texto;
    int numero;

    ss >> texto >> numero;

    return static_cast<uint8_t>(numero);
}

void MenuPartidas::seleccionarPartida() {
    QPushButton *partidaButton = qobject_cast<QPushButton*>(sender());
    this->partidaSeleccionada = (partidaButton->text()).toStdString();
}

void MenuPartidas::elegirPartida() {

    if (this->partidaSeleccionada != "") {
        uint8_t id = obtener_id(this->partidaSeleccionada);

        std::shared_ptr<ListaDePartidas> seleccion = std::make_shared<ListaDePartidas>(this->cliente.id, id);
        cliente.send_queue.push(seleccion);

        qApp->quit();
    }
}

void MenuPartidas::menuCrearPartida() {
    MenuCrearPartida *w = new MenuCrearPartida(this->cliente, this);
    w->show();
    hide();
}

MenuPartidas::~MenuPartidas()
{
    delete ui;
}
