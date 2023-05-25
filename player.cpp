#include "player.h"

Player::Player(QString name,int PlayerNumber, bool Maximizer)
{
    this->name=name;
    this->Score=0;
    this->RemindedPieces=30;
    this->isLost=0;
    this->PlayerNumber=PlayerNumber;
    this->Maximizer=Maximizer;

}

void Player::UpdateScore(int score)
{


    qDebug()<<"score is updated from player: "<<this->PlayerNumber;

    this->Score=score;

    emit SendPlayerSignal({"Update Player Score",QString::number(Score),QString::number(this->PlayerNumber)});

}

void Player::UpdateRemindedPices()
{

    qDebug()<<"Update Player Reminded Pieces: "<<this->PlayerNumber;

    this->RemindedPieces--;

    emit SendPlayerSignal({"Update Player Reminded Pieces",QString::number(this->RemindedPieces),QString::number(this->PlayerNumber)});
}

void Player::setLostFlag(int isLost)
{

    this->isLost=isLost;

    emit SendPlayerSignal({"did player win?",QString::number(isLost),QString::number(this->PlayerNumber)});
//    if(isLost)
//    emit SendPlayerSignal({"did player win?",QString::number(isLost),this->name});

//    else if(!isLost)
//    emit SendPlayerSignal({"did player win?",QString::number(isLost),this->name});
}

void Player::UpdatePlayerTurn()
{

    emit SendPlayerSignal({"Update turn",this->name});
}

void Player::NoValidMovesThisTurn()
{
    emit SendPlayerSignal({"Player skip This Turn",this->name});
}

int Player::IsPlayerMaximizer()
{
    return Maximizer?Maximizer:-1;
}
