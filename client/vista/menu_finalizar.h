#ifndef MENU_FINALIZAR_H
#define MENU_FINALIZAR_H

#include <QMainWindow>

namespace Ui {
class MenuFinalizar;
}

class MenuFinalizar : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuFinalizar(QWidget *parent = nullptr);
    ~MenuFinalizar();

private:
    Ui::MenuFinalizar *ui;
};

#endif // MENU_FINALIZAR_H
