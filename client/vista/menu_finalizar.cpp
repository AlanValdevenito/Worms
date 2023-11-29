#include "menu_finalizar.h"
#include "ui_menu_finalizar.h"

MenuFinalizar::MenuFinalizar(Client &cliente, int resultado, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuFinalizar),
    cliente(cliente),
    resultado(resultado)
{
    ui->setupUi(this);

    QIcon icono(DATA_PATH "/icono.png");
    this->setWindowIcon(icono);

    connectEvents();

    std::string texto = this->resultado ? ("¡Felicidades has ganado!") : ("            Has perdido");
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
