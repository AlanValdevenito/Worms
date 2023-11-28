#include "menu_finalizar.h"
#include "ui_menu_finalizar.h"

MenuFinalizar::MenuFinalizar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuFinalizar)
{
    ui->setupUi(this);
}

MenuFinalizar::~MenuFinalizar()
{
    delete ui;
}
