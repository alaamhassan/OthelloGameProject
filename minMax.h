#ifndef MIN_MAX_H_
#define MIN_MAX_H_

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;


#define MIN_SCORE  -64
#define MAX_SCORE   64

typedef enum{BLACK_PLAYER=1,WHITE_PLAYER=-1} playerType;

copyBoard(int board[BOARD_SIZE][BOARD_SIZE],int newBoard[BOARD_SIZE][BOARD_SIZE]);
int minMax(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth);					
pair<int, int> getBestPlay(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth) ;


#endif /* MIN_MAX_H_ */
