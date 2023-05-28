#ifndef GAMEDISPALYCALCULATION_H
#define GAMEDISPALYCALCULATION_H

#include "boardsquare.h"


int calculateScoreForAPlayer(int PlayerDiskNumber,QList <BoardSquare *> BoardSqaureList);


bool isThereAreValidMoves(QList<std::pair<int,int>>);


#endif // GAMEDISPALYCALCULATION_H
