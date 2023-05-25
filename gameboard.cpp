#include "gameboard.h"

//  QObject::connect(middleWare,&GetAndSindResponseMiddleWare::sendRespnoseToGameBoard,this,&GameBoard::GetResponseFromTheSquare);
GameBoard::GameBoard()//QObject* gameWindow
{


    BoardScene =new QGraphicsScene();//gameWindow
    SetUpBoard();
}


void GameBoard::SetUpBoard()
{
    int Square_XCoordiante=0;
    int Sqaure_YCoordiante=0;

    for(int row=0 ;row<6;row++)
    {
        if(row==5)
        {
            int b=1;
        }
        for(int column=0; column<6; column++)
        {
            BoardSquare * square =
                new BoardSquare(Square_XCoordiante,Sqaure_YCoordiante,BoardSquareNames[row][column]);

            BoardSqaureList.append(square);

            BoardScene->addItem(square);

          bool success=  QObject::connect(square,SIGNAL(sendSignalsToTheGameBoard(QString,int)),this,SLOT(GetResponseFromTheSquare(QString,int)));
            Q_ASSERT(success);

          if(row==1&&column==1)
            {
                square->setSquareState(-1);
                square->DrawDisk();

          }

          qDebug()<<success;

            Square_XCoordiante+=80;
        }
        Square_XCoordiante=0;
        Sqaure_YCoordiante+=80;
    }

    int a=1;
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


void GameBoard::GetResponseFromTheSquare(QString SquareResponse, int PlayerTurn)
{
    //to be able to use the assignment operator
    //convert the QString to string
    std::string action = SquareResponse.toStdString();
   // int squareName =  SquareResponse[1].toInt();

    qDebug()<<"Switch turns";

    if(action.compare("Switch turns")==0)
    {

        playerTurn=(playerTurn+1)%2;

        playerList[playerTurn]->UpdateRemindedPices(3);
        playerList[playerTurn]->UpdateScore(5);

        playerList[playerTurn]->UpdatePlayerTurn();

    }
    else if(action.compare("light the square with red")==0)
    {
        //BoardSqaureList[squareName]->setBrush(Qt::red);

    }
}























//void GameBoard::mousePressEvent(QMouseEvent *event)
//{
//QGraphicsView::mousePressEvent(event);
//}

//void GameBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
// virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;::mousePressEvent(event);
//}

//    QObject::connect(square,&BoardSquare::sendSignalsToTheBoard,this,&GameBoard::GetResponseFromTheSquare);

//           QObject::connect(square,&BoardSquare::sendSignalsToTheBoard,middleWare,&GetAndSindResponseMiddleWare::getResponseFromBoardSquare);
//  QObject::connect(s, SIGNAL(sendSignal(QString)), &game, SLOT(getInput(QString)));
