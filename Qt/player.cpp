#include "player.h"

Player::Player(QString name,int PlayerNumber, bool Maximizer)
{
    this->name=name;
    this->Score=0;
    this->RemindedPieces=30;
    this->isWin=0;
    this->PlayerNumber=PlayerNumber;
    this->Maximizer=Maximizer;

}

void Player::setWinFlag(int isWin)
{
    QString GameOverMessage="";
    if(isWin==1)GameOverMessage=this->name+" Win!";
    else if(isWin==0)GameOverMessage="Draw!";

    emit SendPlayerSignal({"GameOver",QString::number(Score),GameOverMessage});

}

void Player::UpdateScore(int score)
{


    qDebug()<<"score is updated from player: "<<this->PlayerNumber;

    this->Score=score;

    emit SendPlayerSignal({"Update Player Score",QString::number(Score),QString::number(this->PlayerNumber)});

}

void Player::UpdateRemindedPices(int RemindedPieces)
{

    qDebug()<<"Update Player Reminded Pieces: "<<this->PlayerNumber;

    if(RemindedPieces==-1)
    this->RemindedPieces--;

    else
    this->RemindedPieces=RemindedPieces;

    emit SendPlayerSignal({"Update Player Reminded Pieces",QString::number(this->RemindedPieces),QString::number(this->PlayerNumber)});
}

void Player::UpdatePlayerTurn()
{

    emit SendPlayerSignal({"Update turn",this->name});
}

void Player::NoValidMovesThisTurn()
{
    emit SendPlayerSignal({"Player skip This Turn",this->name});
}

int Player::getRemindedPieces()
{
    return RemindedPieces;
}


int Player::IsPlayerMaximizer()
{
    return Maximizer?Maximizer:-1;
}

int Player::getScore()
{
    return Score;
}

void Player::sendSignalToGameWhenComputerPlay()
{
emit SendPlayerSignal({"Computer Play",this->name});
}
