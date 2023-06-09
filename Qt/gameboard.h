#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "boardsquare.h"
#include "player.h"



#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QString>
#include <QTime>
#include<QCoreApplication>

class GameBoard: public QObject
{
    // the Q_OBJECT macro is mandatory for any object that implements signals, slots or properties (from documentation)
    Q_OBJECT
public:
    GameBoard();

    Player* getPlayerList();
    QGraphicsScene* GetBoardScene();

    void SetUpBoard();

    void setPlayerList(QObject * GameWindow,QString Player1Name, QString Player2Name);

    void InitializeBoardForTesting();

    /*disable the board In case of Win,Lose game
    *or when computer play.
    */
    void DisableBoard();

    /*this is just used for testing:
     * as the board will be enabled in the same turn of other
     * operations to avoid time loss.
     */
    void EnableBoard();

    /*this is just for testing:
     * hard code the computer play.
     */
    void computerPlay();


    void delay();

signals:
    void sendturnSignalToGameWindow(QString PlayerTurn);

public slots:
    void GetResponseFromTheSquare(QString SquareResponse,int squareName);


private:
    //a list of the 64 squares of the board
    QList <BoardSquare *> BoardSqaureList;
    QGraphicsScene* BoardScene;
    BoardSquare * boardSqaure;
    Player* playerList[2];

    int playerTurn=0;

    const int BoardSquareNames[8][8]
        =
        {
            {0,1,2,3,4,5,6,7},
            {8,9,10,11,12,13,14,15},
            {16,17,18,19,20,21,22,23},
            {24,25,26,27,28,29,30,31},
            {32,33,34,35,36,37,38,39},
            {40,41,42,43,44,45,46,47},
            {48,49,50,51,52,53,54,55},
            {56,57,58,59,60,61,62,63}
        };


    /*this is just for testing:
     * hard code the computer play.
     */
    //start
    const QString ComputerGame[60]
        =
        {
            "0","1","53","54","55","61",
            "5","6","7","62","8","25","26",
            "27","12","13","14","15","16",
            "17","20","21","22","23","59",
            "60","24","30","31","41","42",
            "56","57","58","63","32","35",
            "38","39","18","19","50","51",
            "40","9","10","11","43","44",
            "45","46","47","48","49","52",
            "2","3","33","34","4"

        };

    int computerIndexTurn=0;

    //end



};

#endif // GAMEBOARD_H



