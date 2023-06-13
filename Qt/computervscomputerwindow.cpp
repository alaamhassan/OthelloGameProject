#include "computervscomputerwindow.h"
#include "ui_computervscomputerwindow.h"
#include "ModesWindow.h"


ModesWindow* modesWindow;


ComputerVsComputerWindow::ComputerVsComputerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerVsComputerWindow)
{


    QStringList ComputerLevels ={"Level 1","Level 2","Level 3", "Level 4", "Level 5",
                                 };

    QString LevelListStyleSheet=
        "QComboBox"
        "{"
        "border-radius:2px;"
        "border:2px solid #1E3706;"
        "border-color:#1E3706;"
        "background: #F1F1F1;"
        "}"
        "QComboBox QScrollBar"
        "{"
        " QListView : solid #1E3706;"
        "width:15px;"
        "}"
        "QComboBox::drop-down"
        "{"
        "border-radius:1px;"
        "border:1px solid #1E3706;"
        "border-color:#1E3706;"
        "background: #90978E;"
        "}"
        "QComboBox::down-arrow"
        "{"
        "image:url(:/computerVScomputerPage/computerVsComputerPage/dropArrow.png);"
        "width:30px;"
        "height:30px;"
        "}"
        "QListView:item"
        "{"
        "border:1px solid #1E3706;"
        "background-color:#F1F1F1;"
        "color:#1E3706;"
        "}"
        "QListView:item:hover"
        "{"
        "border:1px solid #1E3706;"
        "background-color:#1E3706;"
        "color:#F1F1F1;"
        "}"
        "QListView:item:selected"
        "{"
        "border:1px solid #1E3706;"
        "background-color:#1E3706;"
        "color:#F1F1F1;"
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

    ui->setupUi(this);


    ui->computer1LevelList->addItems(ComputerLevels);
    ui->computer1LevelList->setStyleSheet(LevelListStyleSheet);

    ui->computer2LevelList->addItems(ComputerLevels);
    ui->computer2LevelList->setStyleSheet(LevelListStyleSheet);

    ui->backButton->setStyleSheet(BackAndStartStyleSheet);
    ui->nextButton->setStyleSheet(BackAndStartStyleSheet);

    InitializeComputerLevelsMap();
}

ComputerVsComputerWindow::~ComputerVsComputerWindow()
{
    delete ui;
}

void ComputerVsComputerWindow::InitializeComputerLevelsMap()
{
    ComputerLevelsMap["Level 1"]=1;
    ComputerLevelsMap["Level 2"]=2;
    ComputerLevelsMap["Level 3"]=3;
    ComputerLevelsMap["Level 4"]=4;
    ComputerLevelsMap["Level 5"]=5;

    ComputerLevelsMap["Level 6"]=6;
    ComputerLevelsMap["Level 7"]=7;
    ComputerLevelsMap["Level 8"]=8;
    ComputerLevelsMap["Level 9"]=9;
    ComputerLevelsMap["Level 10"]=10;

}

void ComputerVsComputerWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/computerVScomputerPage/computerVsComputerPage/computerVSComputer.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    QDialog::resizeEvent(event);
}

void ComputerVsComputerWindow::on_backButton_clicked()
{
    modesWindow=new ModesWindow();
    hide();
    modesWindow->show();

}


void ComputerVsComputerWindow::on_nextButton_clicked()
{
    int ComputerLevels[2] ={ComputerLevelsMap[ui->computer1LevelList->currentText()],
                              ComputerLevelsMap[ui->computer2LevelList->currentText()]};
    gameWindow=new GameWindow(this, "Computer1","Computer2",ComputerLevels[0],ComputerLevels[1]);
    hide();
    gameWindow->show();



}

