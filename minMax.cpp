

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
        
		if(player==BLACK_PLAYER)
		{	/* BLACK_PLAYER is maximizer (bestPlayScore is the highest score)*/
			if (playscore > bestPlayScore) 
			{
				bestPlayScore = playscore;
				bestPlay = *Position;
			}
			else
			{
				/* Do Nothing */
			}
		}
		else
		{	/* WHITE_PLAYER is minimizer (bestPlayScore is the lowest score)*/
			if (playscore < bestPlayScore) 
			{
				bestPlayScore = playscore;
				bestPlay = *Position;
			}
			else
			{
				/* Do Nothing */
			}
		}
    }
    return bestPlay;
}



int minMax(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth) 
{
	int bestPlayScore;
	int playScore;
	int discRow;
	int discCol;
	vector<vector<int>> newBoard;
	vector<pair<int, int>> PossiblePositions;
    if (depth == 0 || getPossiblePositions(board, player).empty()) {
        return evaluateBoard(board, BLACK_PLAYER);
    }
	else
	{
		/* Do Nothing */
	}
	
	/* BLACK_PLAYER is maximizer (initail score is INT_MIN),WHITE_PLAYER is minimizer(initail score is INT_MAX)  */
	bestPlayScore = (player==BLACK_PLAYER)? MIN_SCORE:MAX_SCORE;
	PossiblePositions = getPossiblePositions(board, player);
	for (auto Position=begin(PossiblePositions); Position!=end(PossiblePositions) ; Position++) 
	{
		discRow = Position->first;
		discCol = Position->second;
		 // put disc in the position @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		playScore = minMax(newBoard, (player == BLACK_PLAYER)? WHITE_PLAYER:BLACK_PLAYER , depth - 1);
		
		if(player==BLACK_PLAYER)
		{	/* BLACK_PLAYER is maximizer (bestPlayScore is the highest score)*/
			bestPlayScore = (playScore > bestPlayScore)? playScore:bestPlayScore;
		}
		else
		{	/* WHITE_PLAYER is minimizer (bestPlayScore is the lowest score)*/
			bestPlayScore =(playScore < bestPlayScore)? playScore:bestPlayScore;
		}
	}
		
	return bestPlayScore;
}