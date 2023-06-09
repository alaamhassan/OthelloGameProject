

#include "minMax.h"


pair<int, int> getBestPlay(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth) {
    int bestPlayScore = (player==BLACK_PLAYER)? MIN_SCORE:MAX_SCORE;
	int discRow ;
    int discCol ;
	int playscore;
	vector<vector<int>> newBoard;
	vector<pair<int, int>> PossiblePositions = getPossiblePositions(board, player);
    pair<int, int> bestPlay = make_pair(-1, -1);
	
    for (auto Position=begin(PossiblePositions); Position!=end(PossiblePositions) ; Position++) 
	{
		discRow = Position->first;
		discCol = Position->second;
        // put disc in the position   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        playscore = minMax(newBoard, (player == BLACK_PLAYER) ? WHITE_PLAYER : BLACK_PLAYER, depth - 1);
        
		
}


