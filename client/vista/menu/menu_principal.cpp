#include "ui_menu_principal.h"
#include "menu_principal.h"

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <QSizePolicy>
#include <QPalette>

MenuPrincipal::MenuPrincipal(Client &cliente, QWidget *parent): 
    QMainWindow(parent), 
    ui(new Ui::MenuPrincipal), 
    cliente(cliente),
    partidas(std::dynamic_pointer_cast<ListaDePartidas>(cliente.recv_queue.pop())->return_list()) 
{

    // Inicializamos la interfaz definida en el archivo .ui
    ui->setupUi(this); 

    QIcon icono(DATA_PATH "/icono.png");
    this->setWindowIcon(icono);

    connectEvents();
}

void MenuPrincipal::connectEvents() {
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)

    connect(ui->partidasButton, &QPushButton::clicked, this, &MenuPrincipal::menuPartidas);
    connect(ui->crearPartidaButton, &QPushButton::clicked, this, &MenuPrincipal::menuCrearPartida);

    // Utilizamos la funcion connect() de Qt para establecer una conexion entre una señal y una ranura.
    // Cuando el boton elegirPartida es clickeado se emite la señal "clicked" y se llama a la ranura MainWindow::elegirPartida.
}

void MenuPrincipal::menuPartidas() {
    MenuPartidas *w = new MenuPartidas(this->cliente, this->partidas, this);
    w->show();
    hide();
}

void MenuPrincipal::menuCrearPartida() {
    MenuCrearPartida *w = new MenuCrearPartida(this->cliente, this);
    w->show();
    hide();
}

MenuPrincipal::~MenuPrincipal() {
    delete ui;
}
