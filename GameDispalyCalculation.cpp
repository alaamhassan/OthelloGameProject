#include"GameDispalyCalculation.h"


int calculateScoreForAPlayer(int PlayerDiskNumber,QList <BoardSquare *> BoardSqaureList)

{
    int Score=0;

    for(int i=0; i<BoardSqaureList.size();i++)

    {
        if(BoardSqaureList[i]->getSquareState()==PlayerDiskNumber)Score++;
    }

    return Score;
}

bool isThereAreValidMoves(QList<std::pair<int,int>> squareValidMoves)
{
    if(squareValidMoves.size()==0)return 0;
    return 1;
}
