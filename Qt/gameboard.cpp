#include "gameboard.h"
#include"GameDispalyCalculation.h"



GameBoard::GameBoard()
{

    BoardScene =new QGraphicsScene();

    playerTurn=0;
    BoardSqaureList={};

    playerList[0]={};
    playerList[1]={};

    SetUpBoard();

    InitializeBoardForTesting();
}


void GameBoard::SetUpBoard()
{
    int Square_XCoordiante=0;
    int Sqaure_YCoordiante=0;

    for(int row=0 ;row<8;row++)
    {

        for(int column=0; column<8; column++)
        {
            BoardSquare * square =
                new BoardSquare(Square_XCoordiante,Sqaure_YCoordiante,BoardSquareNames[row][column]);

            BoardSqaureList.append(square);

            BoardScene->addItem(square);

            bool success=  QObject::connect(square,SIGNAL(sendSignalsToTheGameBoard(QString,QString)),this,SLOT(GetResponseFromTheSquare(QString,QString)));
            Q_ASSERT(success);

          if((row ==3||row==4)&&(column==3||column==4) )
            {
                if((row ==3&&column==4)||(row ==4&&column==3))square->setSquareState(1);

                else square->setSquareState(-1);

                square->DrawDisk();

          }

          qDebug()<<success;

            Square_XCoordiante+=60;
        }
        Square_XCoordiante=0;
        Sqaure_YCoordiante+=60;
    }


}


QGraphicsScene *GameBoard::GetBoardScene()
{
    return BoardScene;
}

void GameBoard::setPlayerList(QObject * GameWindow,QString Player1Name, QString Player2Name)
{
    playerList[0]=new Player(Player1Name,0, 1); //Player1 :maximizer
    bool success=  QObject::connect(playerList[0],SIGNAL(SendPlayerSignal(QStringList)),GameWindow,SLOT(RecievePlayerScoreUpdate(QStringList)));
    Q_ASSERT(success);

    playerList[1]=new Player(Player2Name,1, 0); //player2 minimizer
     success=  QObject::connect(playerList[1],SIGNAL(SendPlayerSignal(QStringList)),GameWindow,SLOT(RecievePlayerScoreUpdate(QStringList)));
    Q_ASSERT(success);
}

void GameBoard::InitializeBoardForTesting()
{
    for(int i=0;i<BoardSqaureList.size();i++)
    {
        if(i%2==0 &&(!BoardSqaureList[i]->getSquareState()) )
        {
            BoardSqaureList[i]->setSquareValidMove(1);

        }
    }

}

void GameBoard::restartBoard()
{


    for(int i=0;i<BoardSqaureList.size();i++)
    {
        BoardSqaureList[i]->hideDisk();
//        if(BoardSqaureList[i]->getSquareState()!=0)
//        {
//            BoardSqaureList[i]->hideDisk();
//            BoardSqaureList[i]->setSquareState(0);
//        }
    }



   // playerList={};

}



void GameBoard::GetResponseFromTheSquare(QString SquareResponse,QString squareName)
{
    //to be able to use the assignment operator
    //convert the QString to string
    std::string action = SquareResponse.toStdString();
   // int squareName =  SquareResponse[1].toInt();

    qDebug()<<"Switch turns";

    QList<std::pair<int,int>> squareValidMoves={std::make_pair(1,2),std::make_pair(1,2)};
    if(action.compare("Switch turns")==0)
    {

        BoardSqaureList[squareName.toInt()]->setSquareState(playerList[playerTurn]->IsPlayerMaximizer());

        playerList[playerTurn]->UpdateRemindedPices();
        playerList[playerTurn]->UpdateScore(calculateScoreForAPlayer(playerList[playerTurn]->IsPlayerMaximizer(),BoardSqaureList));

        playerTurn=(playerTurn+1)%2;
        playerList[playerTurn]->UpdatePlayerTurn();



        if(!isThereAreValidMoves(squareValidMoves))playerList[playerTurn]->NoValidMovesThisTurn();


    }

}

