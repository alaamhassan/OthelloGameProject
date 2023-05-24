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
        for(int column=0; column<6; column++)
        {
            BoardSquare * square =
                new BoardSquare(Square_XCoordiante,Sqaure_YCoordiante,BoardSquareNames[row][column]);

            BoardSqaureList.append(square);

            BoardScene->addItem(square);

          bool success=  QObject::connect(square,SIGNAL(sendSignalsToTheBoard(QStringList)),this,SLOT(GetResponseFromTheSquare(QStringList)));
            Q_ASSERT(success);

          qDebug()<<success;

            Square_XCoordiante+=80;
        }
        Square_XCoordiante=0;
        Sqaure_YCoordiante+=80;
    }
}


QGraphicsScene *GameBoard::GetBoardScene()
{
    return BoardScene;
}

void GameBoard::GetResponseFromTheSquare(QStringList SquareResponse)
{
    //to be able to use the assignment operator
    //convert the QString to string
    std::string action = SquareResponse[0].toStdString();
    int squareName =  SquareResponse[1].toInt();

    if(action.compare("draw disk"))
    {
        BoardSqaureList[squareName]->DrawDisk();
    }
    else if(action.compare("light the square with red"))
    {
        BoardSqaureList[squareName]->setBrush(Qt::red);

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
