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
        "background-color: :#1E3706;"
        "color:#E8E8E8;"
        "}"
    ;


   // ui->MinMaxButton->setStyleSheet(styleSheet);
   // ui->AlphaBetaIterative->setStyleSheet(styleSheet);
    ui->AlphaBeta->setStyleSheet(styleSheet);
    QString lebelStyleSheet=  "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(4, 137, 26, 255), stop:1 rgba(255, 255, 255, 255));"
                              "color:rgb(0, 63, 0);"
                              "border-radius:5px;"
                              "border:1px black;"
                              "margin-top:10px;"
                              "margin-bottom:5px;"
                              "font-size:20px;";
    ui->label->setStyleSheet(lebelStyleSheet);
    ui->label->setAlignment(Qt::AlignCenter);


}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/homePage/HomePage/background2.png");//:/homePage/HomePage/homePageImage.png");//:/backGroundImages/HomePage/bluredImage.jpg
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




//void MainWindow::on_MinMaxButton_clicked()
//{
//    computerVsComputerWindow =new ComputerVsComputerWindow(this);

//    computerVsComputerWindow->show();

//    hide();


//}


void MainWindow::on_AlphaBeta_clicked()
{
    modesWindow =new ModesWindow(this);

    modesWindow->show();

    hide();

}

