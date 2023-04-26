#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

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
    for (int i = 0; i < 2; i++) {
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
        // same steps for score calculation but search through board row by row from right to left
        for (int i = size - 1; i > -1; i--) {
            temp = 0;
            for (int j = 0; j < size; j++) {
                if (board[i][j] != temp && board[i][j] != 0){
                    temp = board[i][j];
                }
                else if (board[i][j] == temp){
                    score += board[i][j] * 2;
                    temp = 0;
                }
            }
        }
    }
    //calculate score if move is up
    else if (move == 'w') {
        // same steps for score calculation but search through board column by column from top to bottom
        for (int i = 0; i < size; i++) {
            temp = 0;
            for (int j = 0; j < size; j++) {
                if (board[j][i] != temp && board[j][i] != 0){
                    temp = board[j][i];
                }
                else if (board[j][i] == temp){
                    score += board[j][i] * 2;
                    temp = 0;
                }
            }
        }
    }
    //calculate score if move is down
    else if (move == 's') {
        // same steps for score calculation but search through board column by column from bottom to top
        for (int i = 0; i < size; i++) {
            temp = 0;
            for (int j = size - 1; j > - 1; j--) {
                if (board[j][i] != temp && board[j][i] != 0){
                    temp = board[j][i];
                }
                else if (board[j][i] == temp){
                    score += board[j][i] * 2;
                    temp = 0;
                }
            }
        }
    }
}

// (generate_random_tile) := Function to generate a random 2-tile after every move is done.
//                           Modifies the board (2D vector).
// Note: A random tile is generated no matter what as long as the game is running (i.e. the game is not finished)
//      because after every successful move, the total number of filled tiles must decrease by at least 1, making
//      room for another tile
void generate_random_tile(int size, vector<vector<int>> &board) {
    // Create an array containing pairs of coordinates (i, j) of currently empty tiles
    pair<int, int> empty_tiles[size * size];
    
    // Find all empty tiles and store their coordinates (i, j) as 'pairs' in the empty_tiles array. Keep count of # of empty tiles. 
    int number_of_empty_tiles = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                empty_tiles[number_of_empty_tiles] = make_pair(i, j);
                number_of_empty_tiles++;
            }
        }
    }

    // Seed the random number generator
    srand(time(0));

    // Select a random index number in the array, thereby selecting a random coordinate from the tiles.
    int random_array_index = rand() % number_of_empty_tiles;
    pair<int, int> random_pair = empty_tiles[random_array_index];

    // Assign the value 2 to the randomly chosen tile
    board[random_pair.first][random_pair.second] = 2;
 
}