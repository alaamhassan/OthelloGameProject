#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QGraphicsView>
#include<QDebug>

GameWindow::GameWindow(QWidget *parent, QString Player1Name, QString Player2Name) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
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
    ui->Player1R->setText(Player1Name);

    ui->Player2->setText(Player2Name);
    ui->Player2R->setText(Player2Name);
}


GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::setPlayerNamesList(QString Player1Name, QString Player2Name)
{
    PlayerNamesList={Player1Name,Player2Name};
}


void GameWindow::InitializePlayerList(QObject * GameWindow)
{
    gameBoard->setPlayerList(GameWindow,PlayerNamesList[0],PlayerNamesList[1]);
}



void GameWindow::RecievePlayerScoreUpdate(QStringList PlayerResponse)
{
    std::string ResponseTitle =PlayerResponse[0].toStdString();
    QString value =PlayerResponse[1];
    int PlayerName=0;

    if(ResponseTitle.compare("Update turn")==0)
    {
        ui->TurnLabel->setText(value);
    }
    else if(ResponseTitle.compare("Player skip This Turn")==0)
    {
//messageBoxtoSkipTurn
    }
    else  PlayerName =PlayerResponse[2].toInt();

    qDebug()<<"Update Player Score: "<<value;

    if(ResponseTitle.compare("Update Player Score")==0)
    {
        qDebug()<<"Update Player Score: "<<value;

        if(PlayerName==0)ui->Player1Score->setText(value);

        else if(PlayerName==1)ui->Player2Score->setText(value);

    }
    if(ResponseTitle.compare("Update Player Reminded Pieces")==0)
    {
        qDebug()<<"Update Player Reminded Pieces: "<<value;


        if(PlayerName==0)ui->player1RemindedPieces->setText(value);

        else if(PlayerName==1)ui->player2RemindedPieces->setText(value);
    }
    if(ResponseTitle.compare("did player win?")==0)
    {
        qDebug()<<"did player win?: "<<value;

        //trigger message win or lose
        if(value.toInt()==-1){} //player is lost
        else if(value.toInt()==1){} //player win

        //restart game
    }



}
void GameWindow::RecievePlayerRemindedPiecesUpdate(QStringList PlayerResponse)
{
    std::string ResponseTitle =PlayerResponse[0].toStdString();
    QString remindedPieces =PlayerResponse[1];
    int PlayerName =PlayerResponse[2].toInt();

    if(ResponseTitle.compare("Update Player Reminded Pieces")==0)
    {
        qDebug()<<"Update Player Reminded Pieces: "<<remindedPieces;

        //playerList[PlayerName]->UpdateRemindedPices(remindedPieces.toInt());

        if(PlayerName==0)ui->player1RemindedPieces->setText(remindedPieces);

        else if(PlayerName==1)ui->player2RemindedPieces->setText(remindedPieces);
    }

}
void GameWindow::RecievePlayerWinOrLostUpdate(QStringList PlayerResponse)
{
    std::string ResponseTitle =PlayerResponse[0].toStdString();
    int isLost =PlayerResponse[1].toInt();
    int PlayerName =PlayerResponse[2].toInt();

    if(ResponseTitle.compare("did player win?"))
    {
        qDebug()<<"did player win?: "<<isLost;
      //  playerList[PlayerName]->setLostFlag(isLost);

        //trigger message win or lose
        if(isLost==-1){} //player is lost
        else if(isLost==1){} //player win

        //restart game
    }
}


