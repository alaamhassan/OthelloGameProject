#include "computervscomputerwindow.h"
#include "ui_computervscomputerwindow.h"
#include "mainwindow.h"

MainWindow *mainWindow;
QString styleSheetForClickedButton="QPushButton{"
                                     "font-size:30px;"
                                     "border-radius:7px;"
                                     "border:1px solid grey;"
                                     "background-color: rgb(0, 63, 0);"
                                     "color:rgb(255,255,230);"
                                     "}";
QString styleSheetForUnClickedButton="QPushButton{"
                                    "font-size:30px;"
                                    "border-radius:7px;"
                                    "border:1px solid grey;"
                                      "background-color: rgb(255,255,230);"
                                       "color:rgb(0, 63, 0);"
                                     "}";
ComputerVsComputerWindow::ComputerVsComputerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerVsComputerWindow)
{
    ui->setupUi(this);

    QStringList levelLists={"Level 1","Level 2","Level 3","Level 4","Level 5"};
    ui->comboBox->addItems(levelLists);

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
    ui->BetaAlphaButton->setStyleSheet(styleSheet);
    ui->BettaAlphaIterativeButton->setStyleSheet(styleSheet);


    QString QcomboBoxStyleSheet=
        "QComboBox:hover{"
         "selectedTextColor : rgb(255,255,230);"
       "selectionColor : rgb(0, 63, 0);"
        "}"

        "QComboBox:pressed{"
        "background-color: rgb(0, 63, 0);"
        "color:rgb(255,255,230);"
        "}"

        "background-color: rgb(255,255,230);"
        "dropDownButtonWidth : 30px;"
        "font : 20px;"
        "selectedTextColor : rgb(255,255,230);"
        "selectionColor : rgb(0, 63, 0);"
        "textColor : rgb(0, 63, 0);";

    ui->comboBox->setStyleSheet(QcomboBoxStyleSheet);

    QString BackAndStartStyleSheet=
        "QPushButton{"
        "font-size:30px;"
        "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(4, 137, 26, 255), stop:1 rgba(255, 255, 255, 255)); "
        "border-radius:7px;"
        "border:1px solid grey;"

       // "background-color: rgb(255,255,230);"
        "color:rgb(0, 63, 0);"
        "}"
        "QPushButton:hover{"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 73, 0, 255), stop:1 rgba(255, 255, 255, 255));"
        "color:rgb(255,255,230);"
        "}"

        "QPushButton:pressed{"
        "background-color: rgb(0, 63, 0);"
        "color:rgb(255,255,230);"
        "}"
        ;

    ui->backButton->setStyleSheet(BackAndStartStyleSheet);
    ui->nextButton->setStyleSheet(BackAndStartStyleSheet);

    QString lebelStyleSheet=  "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(4, 137, 26, 255), stop:1 rgba(255, 255, 255, 255));"
                              "color:rgb(0, 63, 0);"
                              "border-radius:5px;"
                              "border:1px black;"
                              "margin-top:10px;"
                              "margin-bottom:5px;"
                              "font-size:20px;";

    ui->label->setStyleSheet(lebelStyleSheet);
    ui->label->setAlignment(Qt::AlignCenter);

    ui->label_2->setStyleSheet(lebelStyleSheet);
    ui->label_2->setAlignment(Qt::AlignCenter);

}

void ComputerVsComputerWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/backGroundImages/HomePage/bluredImage.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    QDialog::resizeEvent(event);
}

ComputerVsComputerWindow::~ComputerVsComputerWindow()
{
    delete ui;
}


void ComputerVsComputerWindow::on_backButton_clicked()
{
    mainWindow =new MainWindow(this);
    mainWindow->show();
    hide();

}


void ComputerVsComputerWindow::on_nextButton_clicked()
{

    gameWindow =new GameWindow(this);
    gameWindow->show();
    hide();

}


void ComputerVsComputerWindow::on_MinMaxButton_clicked()
{

   ui->MinMaxButton->setStyleSheet(styleSheetForClickedButton);
   ui->BetaAlphaButton->setStyleSheet(styleSheetForUnClickedButton);
   ui->BettaAlphaIterativeButton->setStyleSheet(styleSheetForUnClickedButton);
}

void ComputerVsComputerWindow::on_BetaAlphaButton_clicked()
{
   ui->MinMaxButton->setStyleSheet(styleSheetForUnClickedButton);
   ui->BetaAlphaButton->setStyleSheet(styleSheetForClickedButton);
   ui->BettaAlphaIterativeButton->setStyleSheet(styleSheetForUnClickedButton);
}


void ComputerVsComputerWindow::on_BettaAlphaIterativeButton_clicked()
{
   ui->MinMaxButton->setStyleSheet(styleSheetForUnClickedButton);
   ui->BetaAlphaButton->setStyleSheet(styleSheetForUnClickedButton);
   ui->BettaAlphaIterativeButton->setStyleSheet(styleSheetForClickedButton);
}

