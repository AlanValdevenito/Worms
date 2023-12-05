#include "menu_crear_partida.h"
#include "ui_menu_crear_partida.h"

#include <QGuiApplication>
#include <QScreen>

MenuCrearPartida::MenuCrearPartida(Client &cliente, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuCrearPartida),
    cliente(cliente)
{
    ui->setupUi(this);

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect mainScreenSize = primaryScreen->availableGeometry();
    setGeometry(mainScreenSize);

    QIcon icono(DATA_PATH "/icono.png");
    this->setWindowIcon(icono);

    connectEvents();
}

void MenuCrearPartida::connectEvents() {
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)

    connect(ui->nuevaPartidaButton, &QPushButton::clicked, this, &MenuCrearPartida::crearPartida);
    connect(ui->volverAtrasButton, &QPushButton::clicked, this, &MenuCrearPartida::menuPrincipal);

    // Utilizamos la funcion connect() de Qt para establecer una conexion entre una señal y una ranura.
    // Cuando el boton elegirPartida es clickeado se emite la señal "clicked" y se llama a la ranura MainWindow::elegirPartida.
}

void MenuCrearPartida::crearPartida() {

    std::string cantidadJugadores = (ui->jugadoresComboBox->currentText()).toStdString();
    int mapa = (ui->mapaComboBox->currentIndex());

    //std::cout << mapa << std::endl;

    if ((cantidadJugadores != "Seleccione una opcion") && (mapa > 0)) {

        std::shared_ptr<NuevaPartida> partida = std::make_shared<NuevaPartida>(std::stoi(cantidadJugadores), mapa);
        cliente.send_queue.push(partida);

        qApp->quit();
    }
}

void MenuCrearPartida::menuPrincipal() {
    MenuPrincipal *w = qobject_cast<MenuPrincipal*>(parent());
    w->show();
    close();
}

MenuCrearPartida::~MenuCrearPartida()
{
    delete ui;
}
