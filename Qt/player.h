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
    Player(QString name,int PlayerNumber, bool IsMaximizer, int playerLevel=0);

    void setWinFlag(bool isWin);

    void setIsThereValidMoves(bool isThereValidMoves);

    void UpdateScore(int score);

    void UpdateRemindedPices(int RemindedPieces=-1);

    void UpdatePlayerTurn();

    void NoValidMovesThisTurn();


    int getRemindedPieces();

    int getPlayerLevel();

    QString getPlayerName();

    bool IsThereValidMoves();

    int IsPlayerMaximizer();

    void TakePiecesFromOppenent();

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

    int playerLevel;

    bool IsTherevalidMoves;


};

#endif // PLAYER_H
