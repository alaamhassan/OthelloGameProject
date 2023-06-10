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
         "border-radius:38px;"
         "border: 3px solid #1E3706;"
         "border-color:#1E3706;"

         "background-color:#E8E8E8;"
         "color:#1E3706;"
      "}"
        "QPushButton:hover{"
          "background-color:#1E3706;"
         "color:#E8E8E8;"
         "}"

        "QPushButton:pressed{"
        "background-color:#1E3706;"
        "color:#E8E8E8;"
        "}"
    ;

    ui->AlphaBeta->setStyleSheet(styleSheet);

}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/homePage/HomePage/background2.png");
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


void MainWindow::on_AlphaBeta_clicked()
{
    modesWindow =new ModesWindow(this);

    modesWindow->show();

    hide();

}

