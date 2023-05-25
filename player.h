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
    Player(QString name,int PlayerNumber, bool Maximizer);

    void UpdateScore(int score);

    void UpdateRemindedPices();

    void setLostFlag(int isLost);

    void UpdatePlayerTurn();

    void NoValidMovesThisTurn();

    int IsPlayerMaximizer();
signals:
    void SendPlayerSignal(QStringList );

private:
    //properities:

    QString name;
    int Score;
    int RemindedPieces;
    int PlayerNumber;
    bool Maximizer;
    //if lost:-1, win:1, other:0
    int isLost;


};

#endif // PLAYER_H
