#include "ModesWindow.h"
#include "ui_ModesWindow.h"
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


ModesWindow::ModesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModesWindow)
{
    ui->setupUi(this);

    QStringList levelLists={"Level 1","Level 2","Level 3","Level 4","Level 5"};
    ui->comboBox->addItems(levelLists);

    QString styleSheet=
        "QPushButton{"
        "font-size:30px;"
        "border-radius:38px;"
        "border: 3px solid #1E3706;"
        "border-color:#1E3706;"
        "background-color:#E8E8E8;"
        "color:#1E3706;"
       // "font-family:Assistant Regular;"

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

    QString text="string{"
                   "font-weight:bold;"
                   "}";
    ui->MinMaxButton->setStyleSheet(styleSheet);
   // ui->MinMaxButton->text->setStyleSheet(text);
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
        "border-radius:38px;"
        "border: 1px solid #1E3706;"
        "border-color:#1E3706;"

        "background-color:#90978E;"
        "color:#1E3706;"
        "}"
        ;
    ui->backButton->setStyleSheet(BackAndStartStyleSheet);

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




    ui->chooseModeButton->setStyleSheet("color:#1E3706;font-family:Tenor Sans;");
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

//   ui->MinMaxButton->setStyleSheet(styleSheetForClickedButton);
//   ui->BetaAlphaButton->setStyleSheet(styleSheetForUnClickedButton);
//   ui->BettaAlphaIterativeButton->setStyleSheet(styleSheetForUnClickedButton);



gameWindow =new GameWindow(this,"Player1","Player2");
   gameWindow->show();
   hide();

   //gameWindow->setPlayerNamesList("Player","Computer");

}

void ModesWindow::on_BetaAlphaButton_clicked()
{
//   ui->MinMaxButton->setStyleSheet(styleSheetForUnClickedButton);
//   ui->BetaAlphaButton->setStyleSheet(styleSheetForClickedButton);
//   ui->BettaAlphaIterativeButton->setStyleSheet(styleSheetForUnClickedButton);

   //gameWindow =new GameWindow(this,"Player","Computer");

      computerVsPersonWindow =new ComputerVsPersonWindow();
   computerVsPersonWindow->show();
   hide();



}


void ModesWindow::on_BettaAlphaIterativeButton_clicked()
{
//   ui->MinMaxButton->setStyleSheet(styleSheetForUnClickedButton);
//   ui->BetaAlphaButton->setStyleSheet(styleSheetForUnClickedButton);
//   ui->BettaAlphaIterativeButton->setStyleSheet(styleSheetForClickedButton);


   //gameWindow =new GameWindow(this,"Computer1","Computer2");
  // gameWindow->show();
   computerVsComputerWindow =new ComputerVsComputerWindow();
   computerVsComputerWindow->show();
   hide();



}

