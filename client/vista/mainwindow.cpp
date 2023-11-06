#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <QSizePolicy>
#include <QPalette>

#include <QDebug> // Borrar
#include <iostream> // Borrar

MainWindow::MainWindow(Client &cliente, QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), cliente(cliente) {

    // Inicializamos la interfaz definida en el archivo .ui
    ui->setupUi(this); 

    addItems();
    connectEvents();
}

void MainWindow::addItems() {
    std::shared_ptr<ListaDePartidas> l = std::dynamic_pointer_cast<ListaDePartidas>(cliente.recv_queue.pop());

    std::list<uint8_t> lista = l->return_list();
    for (uint8_t id : lista) {
        QString partida = QString::fromStdString("Partida " + std::to_string((int) id));
        ui->opcionesComboBox->addItem(partida);
    }
}

void MainWindow::connectEvents() {
    connect(ui->elegirPartidaButton, &QPushButton::clicked, this, &MainWindow::elegirPartida);
    connect(ui->nuevaPartidaButton, &QPushButton::clicked, this, &MainWindow::nuevaPartida);

    // Utilizamos la funcion connect() de Qt para establecer una conexion entre una señal y una ranura.
    // Cuando el boton elegirPartida es clickeado se emite la señal "clicked" y se llama a la ranura MainWIndow::elegir.
    // connect(Puntero al boton, Señal que se conectara, Objeto actual, Ranura que se conectara)
}

uint8_t MainWindow::obtener_id(std::string &opcion) {
    std::istringstream ss(opcion);
    std::string texto;
    int numero;

    ss >> texto >> numero;

    return static_cast<uint8_t>(numero);
}

void MainWindow::elegirPartida() {
    // QString partidaSeleccionada = ui->opcionesComboBox->currentText();
    // qDebug() << partidaSeleccionada;

    std::string opcionSeleccionada = (ui->opcionesComboBox->currentText()).toStdString();
    uint8_t id = obtener_id(opcionSeleccionada);

    if (id) {

        std::shared_ptr<ListaDePartidas> seleccion = std::make_shared<ListaDePartidas>(this->cliente.id, id);
    	cliente.send_queue.push(seleccion);

		std::cout << "Te uniste a 'Partida " << int (id) << "'" << std::endl;

        qApp->quit();
    }
}

void MainWindow::nuevaPartida() {
    std::cout << "Nueva partida" << std::endl;

    // qApp->quit(); // Metodo para cerrar toda la aplicacion de Qt.
                  // Cierra todas las ventanas, dialogos y componentes de la aplicacion.
                  // Es util cuando se desea cerrar completamente la aplicacion.

    // close(); // Cierra la ventana actual.
                // Si se tiene una aplicacion con multiples ventanas o dialogos, usar close() cerrara solo la ventana actual sin cerrar la aplicacion por completo.
                // Es util cuando se desea cerrar una ventana especifica y mantener abierta la aplicacion para realizar otras tareas.
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        qApp->quit();

        // close();

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

MainWindow::~MainWindow() {
    delete ui;
}
