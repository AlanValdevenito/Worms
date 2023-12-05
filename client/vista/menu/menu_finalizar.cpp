#include "menu_finalizar.h"
#include "ui_menu_finalizar.h"

#include <QGuiApplication>
#include <QScreen>

MenuFinalizar::MenuFinalizar(Client &cliente, int resultado, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuFinalizar),
    cliente(cliente),
    resultado(resultado)
{
    ui->setupUi(this);

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect mainScreenSize = primaryScreen->availableGeometry();
    setGeometry(mainScreenSize);

    QIcon icono(DATA_PATH "/icono.png");
    this->setWindowIcon(icono);

    connectEvents();

    std::string victoria = "¡Felicidades jugador " + std::to_string((int) this->cliente.id) + " has ganado!";
    std::string derrota = "            Has perdido jugador " + std::to_string((int) this->cliente.id);

    std::string texto = this->resultado ? victoria : derrota;
    ui->resultadoLabel->setText(QString::fromStdString(texto));
}

void MenuFinalizar::connectEvents() {
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)

    connect(ui->salirButton, &QPushButton::clicked, this, &MenuFinalizar::salir);

    // Utilizamos la funcion connect() de Qt para establecer una conexion entre una señal y una ranura.
    // Cuando el boton elegirPartida es clickeado se emite la señal "clicked" y se llama a la ranura MainWindow::elegirPartida.
}

void MenuFinalizar::salir() {
    qApp->quit();
}

MenuFinalizar::~MenuFinalizar()
{
    delete ui;
}
