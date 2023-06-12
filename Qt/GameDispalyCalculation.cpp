#include"GameDispalyCalculation.h"


int calculateScoreForAPlayer(int PlayerDiskNumber,std::vector <BoardSquare *> BoardSqaureList)

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

void Update_ArrayForMinMax(int arr[8][8], char i_org, char j_org, char player) {
    char i = i_org;
    char j = j_org;
    bool flag = 0;

    //updating rows above
    while (i != 0 && (arr[i - 1][j] != 0)) {
        i--;

        if (arr[i][j] == player) {
            i++;
            while (i != i_org) {
                arr[i][j] = player;
                i++;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating rows below
    i = i_org;     j = j_org;     flag = 0;
    while (i != 8 && (arr[i + 1][j] != 0)) {
        i++;

        if (arr[i][j] == player) {
            i--;
            while (i != i_org) {
                arr[i][j] = player;
                i--;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating coloums to the left
    i = i_org;     j = j_org;     flag = 0;
    while (j != 0 && (arr[i][j-1] != 0)) {
        j--;

        if (arr[i][j] == player) {
            j++;
            while (j != j_org) {
                arr[i][j] = player;
                j++;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }


    //updating coloums to the right
    i = i_org;     j = j_org;     flag = 0;
    while (j != 8 && (arr[i][j+1] != 0)) {
        j++;

        if (arr[i][j] == player) {
            j--;
            while (j != j_org) {
                arr[i][j] = player;
                j--;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }


    //updating up_left diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 0 && j!= 0 && (arr[i-1][j-1] != 0)) {
        i--; j--;

        if (arr[i][j] == player) {
            i++; j++;
            while (i != i_org) {
                arr[i][j] = player;
                i++; j++;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating down-right diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i!= 8 && j != 8 && (arr[i+1][j + 1] != 0)) {
        i++;  j++;

        if (arr[i][j] == player) {
            i--;  j--;
            while (j != j_org) {
                arr[i][j] = player;
                i--;  j--;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating up-right diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 0 && j != 8 && (arr[i - 1][j + 1] != 0)) {
        i--;  j++;

        if (arr[i][j] == player) {
            i++;  j--;
            while (j != j_org) {
                arr[i][j] = player;
                i++;  j--;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating down-left diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 8 && j != 0 && (arr[i + 1][j - 1] != 0)) {
        i++;  j--;

        if (arr[i][j] == player) {
            i--;  j++;
            while (j != j_org) {
                arr[i][j] = player;
                i--;  j++;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

}



/*---------------------------------GenerateValidMoves--------------------------*/
// Function to check if a move is valid
bool isValidMoveForMinMax(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int player) {
    // Check if the position is within the board limits
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }

    // Check if the position is empty
    if (board[row][col] != 0) {
        return false;
    }

    // Check if the position is a valid move in any direction
    for (int dirX = -1; dirX <= 1; dirX++) {
        for (int dirY = -1; dirY <= 1; dirY++) {
            // Skip the current position and diagonals
            if (dirX == 0 && dirY == 0) {
                continue;
            }

            int currX = row + dirX;
            int currY = col + dirY;

            // Check if there is an opponent piece adjacent in the current direction
            if (currX >= 0 && currX < BOARD_SIZE && currY >= 0 && currY < BOARD_SIZE && board[currX][currY] != player && board[currX][currY] != 0) {
                // Continue moving in the current direction until reaching a player's piece or an empty position
                while (currX >= 0 && currX < BOARD_SIZE && currY >= 0 && currY < BOARD_SIZE && board[currX][currY] != player && board[currX][currY] != 0) {
                    currX += dirX;
                    currY += dirY;
                }

                // If a player's piece is found, the move is valid
                if (currX >= 0 && currX < BOARD_SIZE && currY >= 0 && currY < BOARD_SIZE && board[currX][currY] == player) {
                    return true;
                }
            }
        }
    }

    // No valid move found in any direction
    return false;
}

// Function to return all possible positions to play in Othello
std::vector<std::pair<int, int>> getPossiblePositionsForMinMax(int board[BOARD_SIZE][BOARD_SIZE], int player) {
    std::vector<std::pair<int, int>> possiblePositions;

    // Loop through the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Check if the current position is empty
            if (board[i][j] == 0) {
                // Check if the current position is a valid move for the player
                if (isValidMoveForMinMax(board, i, j, player)) {
                    possiblePositions.push_back(std::make_pair(i, j));
                }
            }
        }
    }

    return possiblePositions;
}

int getOpponent(int player) {
    return (player == 1) ? -1 : 1;
}

int countPlayerDiscs(int board[BOARD_SIZE][BOARD_SIZE], int player) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == player) {
                count++;
            }
        }
    }
    return count;
}

int evaluateBoard(int board[BOARD_SIZE][BOARD_SIZE], int player) {
    int playerDiscs = countPlayerDiscs(board, player);
    int opponentDiscs = countPlayerDiscs(board, getOpponent(player));
    return playerDiscs - opponentDiscs;
}
