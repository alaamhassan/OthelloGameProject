#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "computervscomputerwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    //void on_MinMaxButton_clicked();

    void on_AlphaBeta_clicked();

private:
    Ui::MainWindow *ui;
    ComputerVsComputerWindow* computerVsComputerWindow;


};
#endif // MAINWINDOW_H
