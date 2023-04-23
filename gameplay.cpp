#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to initialize the board takes size of the board and the board itself as input and returns the 2D board
void initializeBoard(int size, vector<vector<int>> &board) {
    // Resize the board with the given size and initialize its elements with 0(empty positions)
    for(int i= 0; i < size; i++){
        vector<int> row;
        for(int j = 0; j < size; j++){
            row.push_back(0);
        }
        board.push_back(row);
    }

    // Seed the random number generator
    srand(time(0));

    // Place two 2s at random positions on the board
    for (int i = 0; i < 8; i++) {
        int x, y;
        // Generate random positions until an empty position is found
        while (true) {
            x = rand() % size;
            y = rand() % size;
            // If the position is empty, place a 2 there
            if (board[x][y] == 0) {
                board[x][y] = 2;
                break;
            }
        }
    }
}

//Function to calculate the score of the board after a move
void calculateScore(char move, int &score, int size, vector<vector<int>> &board) {
    int temp = 0;
    // calculate score if move is left
    if (move == 'a') {
        // search through board row by row from left to right
        for (int i = 0; i < size; i++) {
            //reset temp to 0 for each row
            temp = 0;
            for (int j = 0; j < size; j++) {
                // if current element of board is not equal to the previous element, previous element becomes the current element
                if (board[i][j] != temp && board[i][j] != 0){
                    temp = board[i][j];
                }
                //if previous element equal to current element, add their sum to score
                else if (board[i][j] == temp){
                    score += board[i][j] * 2;
                    // set temp(previous element) to 0, so that no odd number of adjacent, similar tiles are added to score
                    temp = 0;
                }
            }
        }
    }
    // calculate score if move is right
    else if (move == 'd') {
        // search through board row by row from right to left
        for (int i = size - 1; i > -1; i--) {
            //reset temp to 0 for each row
            temp = 0;
            for (int j = 0; j < size; j++) {
                // if current element of board is not equal to the previous element, previous element becomes the current element
                if (board[i][j] != temp && board[i][j] != 0){
                    temp = board[i][j];
                }
                //if previous element equal to current element, add their sum to score
                else if (board[i][j] == temp){
                    score += board[i][j] * 2;
                    // set temp(previous element) to 0, so that no odd number of adjacent, similar tiles are added to score
                    temp = 0;
                }
            }
        }
    }
    //calculate score if move is up
    else if (move == 'w') {
        // search through board column by column from top to bottom
        for (int i = 0; i < size; i++) {
            //reset temp to 0 for each column
            temp = 0;
            for (int j = 0; j < size; j++) {
                // if current element of board is not equal to the previous element, previous element becomes the current element
                if (board[j][i] != temp && board[j][i] != 0){
                    temp = board[j][i];
                }
                //if previous element equal to current element, add their sum to score
                else if (board[j][i] == temp){
                    score += board[j][i] * 2;
                    // set temp(previous element) to 0, so that no odd number of adjacent, similar tiles are added to score
                    temp = 0;
                }
            }
        }
    }
    //calculate score if move is down
    else if (move == 's') {
        // search through board column by column from bottom to top
        for (int i = 0; i < size; i++) {
            //reset temp to 0 for each column
            temp = 0;
            for (int j = size - 1; j > - 1; j--) {
                // if current element of board is not equal to the previous element, previous element becomes the current element
                if (board[j][i] != temp && board[j][i] != 0){
                    temp = board[j][i];
                }
                //if previous element equal to current element, add their sum to score
                else if (board[j][i] == temp){
                    score += board[j][i] * 2;
                    // set temp(previous element) to 0, so that no odd number of adjacent, similar tiles are added to score
                    temp = 0;
                }
            }
        }
    }
}
