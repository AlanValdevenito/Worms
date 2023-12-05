#include "menu_partidas.h"
#include "ui_menu_partidas.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>

MenuPartidas::MenuPartidas(Client &cliente, std::list<uint8_t> &partidas, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuPartidas),
    cliente(cliente),
    partidas(partidas),
    partidaSeleccionada("")
{
    ui->setupUi(this);

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect mainScreenSize = primaryScreen->availableGeometry();
    setGeometry(mainScreenSize);

    QIcon icono(DATA_PATH "/icono.png");
    this->setWindowIcon(icono);

    addItems();
    connectEvents();
}

void MenuPartidas::addItems() {

    QVBoxLayout *layout = new QVBoxLayout();
    for (uint8_t id : this->partidas) {
        QString partida = QString::fromStdString("Partida " + std::to_string((int) id));

        QPushButton *partidaButton = new QPushButton(partida, this);
        partidaButton->setStyleSheet("QPushButton {" 
                                     "  border: none;"
                                     "  border-top: 1px solid gray;"
                                     "  border-bottom: 1px solid gray;"
                                     "  text-align: left;"
                                     "  padding-left: 5px;"
                                     "  background-color: transparent;"
                                     "  color: gray;" 
                                     "}"
                                     "QPushButton:pressed {"
                                     "  background-color: gray;"
                                     "}"
                                     "QPushButton {" 
                                     "image: none;"
                                     "}"
                                     );

        layout->addWidget(partidaButton);
    }

    layout->addStretch(1);
    ui->scrollContentsPartida->setLayout(layout);

}

void MenuPartidas::connectEvents() {
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)

    connect(ui->elegirPartidaButton, &QPushButton::clicked, this, &MenuPartidas::elegirPartida);
    connect(ui->volverAtrasButton, &QPushButton::clicked, this, &MenuPartidas::menuPrincipal);

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

void MenuPartidas::menuPrincipal() {
    MenuPrincipal *w = qobject_cast<MenuPrincipal*>(parent());
    w->show();
    close();
}

MenuPartidas::~MenuPartidas()
{
    delete ui;
}
