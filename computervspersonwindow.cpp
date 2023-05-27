#include "computervspersonwindow.h"
#include "ui_computervspersonwindow.h"
#include "ModesWindow.h"

extern ModesWindow* modesWindow;


ComputerVsPersonWindow::ComputerVsPersonWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerVsPersonWindow)
{

QString LevelListStyleSheet=
        "QListWidget"
    "{"
  "border-radius:2px;"
  "border: 2px solid #1E3706;"
  "border-color:#1E3706;"
   " background : #F1F1F1;"
    "}"
   " QListWidget QScrollBar"

   " {"
   " background : solid #1E3706;"
"width:15px;"
   " }"
      "QListWidget:item"
      "{"
      "border:1px solid #1E3706;"
      "background-color:#F1F1F1;"
      "color:#1E3706;"
      "}"
      "QListWidget:item:hover"
      "{"
      "border:1px solid #1E3706;"
      "background-color:#1E3706;"
      "color:#F1F1F1;"
      "}"
      "QListWidget:item:selected"
      "{"
      "border:1px solid #1E3706;"
      "background-color:#1E3706;"
      "color:#F1F1F1;"
      "}"
        ;
    ui->setupUi(this);
    ui->levelList->addItems({"Level 1","Level 2","Level 3", "Level 4", "Level 5",
                            "Level 6","Level 7","Level 8", "Level 9", "Level 10"});
    ui->levelList->setStyleSheet(LevelListStyleSheet);


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

    ui->nextButton->setStyleSheet(BackAndStartStyleSheet);
    ui->backButton->setStyleSheet(BackAndStartStyleSheet);

}

ComputerVsPersonWindow::~ComputerVsPersonWindow()
{
    delete ui;
}

void ComputerVsPersonWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/homePage/HomePage/chooseLevel.png");//:/homePage/HomePage/homePageImage.png");//:/backGroundImages/HomePage/bluredImage.jpg
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    QDialog::resizeEvent(event);
}

void ComputerVsPersonWindow::on_backButton_clicked()
{
    modesWindow =new ModesWindow(this);
    modesWindow->show();
    hide();
}



void ComputerVsPersonWindow::on_nextButton_clicked()
{
    QStringList computer1Level ={ui->levelList->currentItem()->text()};
    gameWindow =new GameWindow(this,"Player","Computer",computer1Level);
    gameWindow->show();
    hide();
}

