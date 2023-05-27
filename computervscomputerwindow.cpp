#include "computervscomputerwindow.h"
#include "ui_computervscomputerwindow.h"
#include "ModesWindow.h"


ModesWindow* modesWindow;


ComputerVsComputerWindow::ComputerVsComputerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerVsComputerWindow)
{


    QStringList ComputerLevels ={"Level 1","Level 2","Level 3", "Level 4", "Level 5",
                                  "Level 6","Level 7","Level 8", "Level 9", "Level 10"};

    QString LevelListStyleSheet=
        "QListView"
        "{"
        "border-radius:2px;"
        "border:2px solid #1E3706;"
        "border-color:#1E3706;"
        "background: #F1F1F1;"
        "}"
        " QListView QScrollBar"
        " {"
        " QListView : solid #1E3706;"
        "width:15px;"
        " }"
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
        "border-radius:38px;"
        "border: 1px solid #1E3706;"
        "border-color:#1E3706;"

        "background-color:#90978E;"
        "color:#1E3706;"
        "}"
        ;

    ui->setupUi(this);


    ui->computer1LevelList->addItems(ComputerLevels);
    ui->computer1LevelList->setStyleSheet(LevelListStyleSheet);

    ui->computer2LevelList->addItems(ComputerLevels);
    ui->computer2LevelList->setStyleSheet(LevelListStyleSheet);

    ui->backButton->setStyleSheet(BackAndStartStyleSheet);
    ui->nextButton->setStyleSheet(BackAndStartStyleSheet);

}

ComputerVsComputerWindow::~ComputerVsComputerWindow()
{
    delete ui;
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
    modesWindow->show();
    hide();
}


void ComputerVsComputerWindow::on_nextButton_clicked()
{
    QStringList ComputerLevels ={ui->computer1LevelList->currentText(),
                              ui->computer2LevelList->currentText()};
    gameWindow=new GameWindow(this, "Computer1","Computer2",ComputerLevels);
    gameWindow->show();
    hide();


}

