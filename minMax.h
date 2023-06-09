#ifndef MIN_MAX_H_
#define MIN_MAX_H_

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;


#define MIN_SCORE  -64
#define MAX_SCORE   64

typedef enum{BLACK_PLAYER=1,WHITE_PLAYER=-1} playerType;



int minMax(vector<vector<int>>& board, int player, int depth);					//int board[BOARD_SIZE][BOARD_SIZE]
pair<int, int> getBestPlay(vector<vector<int>>& board, int player, int depth) ;


#endif /* MIN_MAX_H_ */