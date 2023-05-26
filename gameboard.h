#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "boardsquare.h"
#include "player.h"



#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QString>



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

    void restartBoard();


signals:
    void sendturnSignalToGameWindow(QString PlayerTurn);

public slots:
    void GetResponseFromTheSquare(QString SquareResponse,QString squareName);


private:
    //a list of the 36 squares of the board
    QList <BoardSquare *> BoardSqaureList;
    QGraphicsScene* BoardScene;
    BoardSquare * boardSqaure;
    Player* playerList[2];

    int playerTurn=0;

    const QString BoardSquareNames[8][8]
        =
        {
            {"0","1","2","3","4","5","6","7"},
            {"8","9","10","11","12","13","14","15"},
            {"16","17","18","19","20","21","22","23"},
            {"24","25","26","27","28","29","30","31"},
            {"32","33","34","35","36","37","38","39"},
            {"40","41","42","43","44","45","46","47"},
            {"48","49","50","51","52","53","54","55"},
            {"56","57","58","59","60","61","62","63"}
        };





};

#endif // GAMEBOARD_H



