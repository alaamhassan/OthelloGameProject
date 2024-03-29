#include "ModesWindow.h"
#include "ui_ModesWindow.h"
#include "mainwindow.h"

MainWindow *mainWindow;

ModesWindow::ModesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModesWindow)
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
        "background-color: #1E3706;"
        "color:#E8E8E8;"
        "}"

        ;

    QString BackAndStartStyleSheet=
        "QPushButton{"
        "font-size:30px;"
        "border-radius:10px;"
        "border: 2px solid #1E3706;"
        "border-color:#1E3706;"
        "background-color:#90978E;"
        "color:#1E3706;"
        "}"

        "QPushButton:hover{"
        "border-radius:10px;"
        "border: 2px solid #90978E;"
        "border-color:#90978E;"
        "background-color:#1E3706;"
        "color:#90978E;"
        "}"

        "QPushButton:pressed{"
        "border-radius:10px;"
        "border: 2px solid #90978E;"
        "border-color:#90978E;"
        "background-color:#1E3706;"
        "color:#90978E;"
        "}"
        ;



    ui->MinMaxButton->setStyleSheet(styleSheet);
    ui->BetaAlphaButton->setStyleSheet(styleSheet);
    ui->BettaAlphaIterativeButton->setStyleSheet(styleSheet);

    ui->backButton->setStyleSheet(BackAndStartStyleSheet);

}


void ModesWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/homePage/HomePage/chooseMode.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    QDialog::resizeEvent(event);
}


ModesWindow::~ModesWindow()
{
    delete ui;
}


void ModesWindow::on_backButton_clicked()
{
    mainWindow =new MainWindow(this);
    mainWindow->show();
    hide();

}



void ModesWindow::on_MinMaxButton_clicked()
{
    gameWindow =new GameWindow(this,"Player1","Player2");
    gameWindow->show();
    hide();
}

void ModesWindow::on_BetaAlphaButton_clicked()
{
    computerVsPersonWindow =new ComputerVsPersonWindow();
    computerVsPersonWindow->show();
    hide();
}


void ModesWindow::on_BettaAlphaIterativeButton_clicked()
{
   computerVsComputerWindow =new ComputerVsComputerWindow();
   computerVsComputerWindow->show();
   hide();
}

