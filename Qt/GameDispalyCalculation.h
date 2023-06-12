#ifndef GAMEDISPALYCALCULATION_H
#define GAMEDISPALYCALCULATION_H

#include "boardsquare.h"

const int BOARD_SIZE = 8;


int calculateScoreForAPlayer(int PlayerDiskNumber,std::vector <BoardSquare *> BoardSqaureList);


bool isThereAreValidMoves(QList<std::pair<int,int>>);

void Update_ArrayForMinMax(int arr[8][8], char i_org, char j_org, char player);

bool isValidMoveForMinMax(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int player);

std::vector<std::pair<int, int>> getPossiblePositionsForMinMax(int board[BOARD_SIZE][BOARD_SIZE], int player);

int getOpponent(int player);

int countPlayerDiscs(int board[BOARD_SIZE][BOARD_SIZE], int player);

int evaluateBoard(int board[BOARD_SIZE][BOARD_SIZE], int player);

#endif // GAMEDISPALYCALCULATION_H
