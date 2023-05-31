#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "ModesWindow.h"
#include "computervscomputerwindow.h"
#include "computervspersonwindow.h"

#include <QGraphicsView>
#include<QDebug>
#include<QMessageBox>

ModesWindow *optionsWindow;
ComputerVsComputerWindow* computerVsComputerWindow;
ComputerVsPersonWindow* computerVsPersonWindow;

GameWindow::GameWindow(QWidget *parent, QString Player1Name, QString Player2Name, QStringList PlayerLevels) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{

    QString ButtonStyleSheet=
        "QPushButton{"
        "font-size:20px;"
        "border: 2px solid #1E3706;"
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

    QString BackStyleSheet=
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

    gameBoard =new GameBoard();

    PlayerNamesList={Player1Name,Player2Name} ;
    InitializePlayerList(this);

    ui->graphicsView->setScene(gameBoard->GetBoardScene());

    ui->graphicsView->setMouseTracking(true);

    setMouseTracking(true);

    qDebug()<<"mouse:"<<(ui->graphicsView->hasMouseTracking());

    ui->graphicsView->show();


    ui->TurnLabel->setText(Player1Name);

    ui->Player1->setText(Player1Name);
    ui->Player1Score->setText("2");

    ui->Player1R->setText(Player1Name);
    ui->player1RemindedPieces->setText("30");

    ui->Player2->setText(Player2Name);
    ui->Player2Score->setText("2");
    ui->Player2R->setText(Player2Name);
    ui->player2RemindedPieces->setText("30");

    ui->RestartButton->setStyleSheet(ButtonStyleSheet);
    ui->backButton->setStyleSheet(BackStyleSheet);

    ui->graphicsView->setStyleSheet("background-color:#000000;");
}


GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/homePage/HomePage/GAMEWINDOW (2).png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    QDialog::resizeEvent(event);
}

void GameWindow::setPlayerNamesList(QString Player1Name, QString Player2Name)
{
    PlayerNamesList={Player1Name,Player2Name};
}


void GameWindow::InitializePlayerList(QObject * GameWindow)
{
    if(isRestart)
    {
        int a=1;
    }
    gameBoard->setPlayerList(GameWindow,PlayerNamesList[0],PlayerNamesList[1]);
}



void GameWindow::RecievePlayerScoreUpdate(QStringList PlayerResponse)
{
    std::string ResponseTitle =PlayerResponse[0].toStdString();
    QString value =PlayerResponse[1];
    int PlayerNumber=0;

    if(ResponseTitle.compare("Update turn")==0)
    {
        ui->TurnLabel->setText(value+" Turn");
    }
    else if(ResponseTitle.compare("Player skip This Turn")==0)
    {
//messageBoxtoSkipTurn
    }
    else  PlayerNumber =PlayerResponse[2].toInt();

    qDebug()<<"Update Player Score: "<<value;

    if(ResponseTitle.compare("Update Player Score")==0)
    {
        qDebug()<<"Update Player Score: "<<value;

        if(PlayerNumber==0)ui->Player1Score->setText(value);

        else if(PlayerNumber==1)ui->Player2Score->setText(value);

    }
    else if(ResponseTitle.compare("Update Player Reminded Pieces")==0)
    {
        qDebug()<<"Update Player Reminded Pieces: "<<value;


        if(PlayerNumber==0)ui->player1RemindedPieces->setText(value);

        else if(PlayerNumber==1)ui->player2RemindedPieces->setText(value);
    }
    else if(ResponseTitle.compare("Player win")==0)
    {
        qDebug()<<"did player win?: "<<value;

        //trigger message win or lose
        if(value.toInt()==-1){} //player is lost
        else if(value.toInt()==1){} //player win

        //disableButtons

        ui->RestartButton->setEnabled(false);
        ui->backButton->setEnabled(false);

        QString WinPlayer= PlayerNamesList[PlayerNumber] +" Win!";
      //  if()
        DisplayGameOver(WinPlayer);
    }




}

void GameWindow::DisplayGameOver(QString Message)
{

    //draw semi-transparent rect

    QGraphicsRectItem* transparentPanal =new QGraphicsRectItem(0,0,480,480);

    QBrush transparentbrush;
    transparentbrush.setStyle(Qt::SolidPattern);
    transparentbrush.setColor("#1E3706");
    transparentPanal->setBrush(transparentbrush);
    transparentPanal->setOpacity(0.43);
    gameBoard->GetBoardScene()->addItem(transparentPanal);


    QGraphicsRectItem* GameOverPanal =new QGraphicsRectItem(10,10,460,460);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor("#F1F1F1");
    GameOverPanal->setBrush(brush);
    GameOverPanal->setOpacity(0.75);
    gameBoard->GetBoardScene()->addItem(GameOverPanal);


    //create playAgain button
  //  Button* playAgainButton=new Button(QString("Play Again"));



    //create return to modes window button




}

void GameWindow::on_RestartButton_clicked()
{
    QMessageBox::StandardButton replay =QMessageBox::question(this,"Restart"
                          ,"Are you sure you want to restart the game?",
                          QMessageBox::Yes|QMessageBox::No);

    if(replay==QMessageBox::Yes)
    {
        gameBoard =new GameBoard();
        InitializePlayerList(this);
        ui->graphicsView->setScene(gameBoard->GetBoardScene());


        ui->Player1Score->setText("2");
        ui->player1RemindedPieces->setText("30");
        ui->Player2Score->setText("2");
        ui->player2RemindedPieces->setText("30");

    }

}


void GameWindow::on_backButton_clicked()
{
    QMessageBox::StandardButton replay =QMessageBox::question(this,"Back"
                                                               ,"You will lose your progress if you clicked back!",
                                                               QMessageBox::Yes|QMessageBox::No);

    if(replay==QMessageBox::Yes)
    {
        if(PlayerNamesList[0]=="Player1")
        {
            optionsWindow =new ModesWindow(this);
            optionsWindow->show();
            hide();
        }
        else if (PlayerNamesList[0]=="Player")
        {
            computerVsPersonWindow =new ComputerVsPersonWindow();
            computerVsPersonWindow->show();
            hide();

        }
        else if (PlayerNamesList[0]=="Computer1")
        {
            computerVsComputerWindow = new ComputerVsComputerWindow();
            computerVsComputerWindow->show();
            hide();
        }


    }

}

