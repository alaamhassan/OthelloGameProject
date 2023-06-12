#ifndef PLAYER_H
#define PLAYER_H

#include "QString"
#include "QObject"
#include "QDebug"

class Player: public QObject
{
    Q_OBJECT
public:
    //functions
    Player(QString name,int PlayerNumber, bool IsMaximizer);

    void setWinFlag(bool isWin);

    void UpdateScore(int score);

    void UpdateRemindedPices(int RemindedPieces=-1);

    void UpdatePlayerTurn();

    void NoValidMovesThisTurn();

    int getRemindedPieces();

    int IsPlayerMaximizer();

    int getScore();

signals:
    void SendPlayerSignal(QStringList );

private:
    //properities:

    QString name;
    int Score;
    int RemindedPieces;
    int PlayerNumber;
    bool IsMaximizer;
    //if win:1, draw:0
    bool isWin;


};

#endif // PLAYER_H
