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

void MenuPrincipal::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        qApp->quit();

        // qApp->quit(); // Metodo para cerrar toda la aplicacion de Qt.
                         // Cierra todas las ventanas, dialogos y componentes de la aplicacion.
                         // Es util cuando se desea cerrar completamente la aplicacion.

        // close(); // Cierra la ventana actual.
                    // Si se tiene una aplicacion con multiples ventanas o dialogos, usar close() cerrara solo la ventana actual sin cerrar la aplicacion por completo.
                    // Es util cuando se desea cerrar una ventana especifica y mantener abierta la aplicacion para realizar otras tareas.

        // Diseñar la nueva ventana en Qt Designer:
        // Abre Qt Designer y crea un nuevo archivo .ui para la segunda ventana si aún no lo has hecho.
        // Diseña la interfaz de la segunda ventana con los elementos deseados, como una imagen de fondo diferente y un mensaje nuevo.

        // Crea una nueva clase para la segunda ventana:
        // Crea una nueva clase en tu proyecto que herede de QMainWindow. Por ejemplo, podrías llamarla SecondWindow.
        // En el constructor de esta clase, utiliza ui->setupUi(this) para inicializar la interfaz definida en el nuevo archivo .ui que creaste en el paso 1.

        // Modifica el manejador de eventos keyPressEvent en MainWindow:
        // En la función keyPressEvent de tu MainWindow actual, cuando se presione ENTER, en lugar de llamar qApp->quit(), crea una instancia de SecondWindow y muéstrala.
        // Crea una instancia de la segunda ventana
        // SecondWindow *secondWindow = new SecondWindow();
        // Muestra la segunda ventana
        // secondWindow->show();    

        // Gestiona la transición entre ventanas:
        // Asegúrate de que las instancias de SecondWindow se gestionen adecuadamente para evitar fugas de memoria cuando las ventanas se cierran.
        // Puedes considerar cerrar la ventana actual o simplemente ocultarla según tus necesidades.
    }
}

MenuPrincipal::~MenuPrincipal() {
    delete ui;
}
