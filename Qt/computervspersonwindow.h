#ifndef COMPUTERVSPERSONWINDOW_H
#define COMPUTERVSPERSONWINDOW_H

#include <QDialog>

#include "gamewindow.h"

namespace Ui {
class ComputerVsPersonWindow;
}

class ComputerVsPersonWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerVsPersonWindow(QWidget *parent = nullptr);
    ~ComputerVsPersonWindow();

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::ComputerVsPersonWindow *ui;

    GameWindow* gameWindow;
};

#endif // COMPUTERVSPERSONWINDOW_H
