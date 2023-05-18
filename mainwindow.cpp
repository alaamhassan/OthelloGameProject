#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     QString styleSheet=
       "QPushButton{"
                         "font-size:30px;"
                         //        "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(4, 137, 26, 255), stop:1 rgba(255, 255, 255, 255)); "
                         "border-radius:7px;"
                         "border:1px solid grey;"

                         "background-color: rgb(255,255,230);"
                         "color:rgb(0, 63, 0);"
      "}"
        "QPushButton:hover{"
                          "background-color: rgb(0, 63, 0);"
                         "color:rgb(255,255,230);"
                         "}"

        "QPushButton:pressed{"
        "background-color: rgb(0, 63, 0);"
        "color:rgb(255,255,230);"
        "}"
    ;


    ui->MinMaxButton->setStyleSheet(styleSheet);
    ui->AlphaBetaIterative->setStyleSheet(styleSheet);
    ui->AlphaBeta->setStyleSheet(styleSheet);

    ui->label->setStyleSheet("font-size:20px");
    ui->label->setStyleSheet("color: rgb(75, 150, 0)");



}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/backGroundImages/HomePage/bluredImage.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_MinMaxButton_clicked()
{
    computerVsComputerWindow =new ComputerVsComputerWindow(this);

    computerVsComputerWindow->show();

    hide();


}


void MainWindow::on_AlphaBeta_clicked()
{
    computerVsComputerWindow =new ComputerVsComputerWindow(this);

    computerVsComputerWindow->show();

    hide();

}

