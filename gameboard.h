#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "boardsquare.h"
#include "getandsindresponsemiddleware.h"
#include "player.h"

#include <QPainter>
#include <QGraphicsScene>
#include<QDebug>
#include <QString>



class GameBoard: public QObject
{
    // the Q_OBJECT macro is mandatory for any object that implements signals, slots or properties (from documentation)
    Q_OBJECT
public:
    GameBoard();//QObject* gameWindow

    void SetUpBoard();
    QGraphicsScene* GetBoardScene();

    void setPlayerList(QObject * GameWindow,QString Player1Name, QString Player2Name);

signals:
    void sendturnSignalToGameWindow(QString PlayerTurn);

public slots:
    void GetResponseFromTheSquare(QString SquareResponse, int PlayerTurn);


private:
    //a list of the 36 squares of the board
    QList <BoardSquare *> BoardSqaureList;
    const QString BoardSquareNames[6][6]
        =
        {
            {"0","1","2","3","4","5"},
            {"6","7","8","9","10","11"},
            {"12","13","14","15","16","17"},
            {"18","19","20","21","22","23"},
            {"24","25","26","27","28","29"},
            {"30","31","32","33","34","35"}
        };

    QGraphicsScene* BoardScene;
    BoardSquare * boardSqaure;

    GetAndSindResponseMiddleWare* middleWare;

    Player* playerList[2];


    int playerTurn=0;
};

#endif // GAMEBOARD_H


//    const QString BoardSquareNames[6][6]
//    =
//    {
//    {"00","01","02","03","04","05"},
//    {"10","11","12","13","14","15"},
//    {"20","21","22","23","24","25"},
//    {"30","31","32","33","34","35"},
//    {"40","41","42","43","44","45"},
//    {"50","51","52","53","54","55"}
//    };
