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

void Player::UpdateScore(int Score)
{


    qDebug()<<"score is updated from player: "<<this->PlayerNumber;

    this->Score=Score;

    emit SendPlayerSignal({"Update Player Score",QString::number(Score),QString::number(this->PlayerNumber)});

}

void Player::UpdateRemindedPices(int RemindedPices)
{

    qDebug()<<"Update Player Reminded Pieces: "<<this->PlayerNumber;

    this->RemindedPieces=RemindedPices;

    emit SendPlayerSignal({"Update Player Reminded Pieces",QString::number(RemindedPices),QString::number(this->PlayerNumber)});
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
