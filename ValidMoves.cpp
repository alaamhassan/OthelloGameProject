#include <iostream>
#include <vector>
#include "ValidMoves.h"

using namespace std;


// Function to initialize the Othello board
void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    board[3][3] = -1;
    board[3][4] = 1;
    board[4][3] = 1;
    board[4][4] = -1;
}

// Function to check if a move is valid
bool isValidMove(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int player) {
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
vector<pair<int, int>> getPossiblePositions(int board[BOARD_SIZE][BOARD_SIZE], int player) {
    vector<pair<int, int>> possiblePositions;

    // Loop through the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Check if the current position is empty
            if (board[i][j] == 0) {
                // Check if the current position is a valid move for the player
                if (isValidMove(board, i, j, player)) {
                    possiblePositions.push_back(make_pair(i, j));
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

