#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

// Function to initialize the board 
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
    
    // For score calculation, four directions need to considered: up, down, left and right.
    
    // *Explanation of logic*
    // If move is in left direction, then we must loop through each element of the board from left to right(similar logic for rest of directions).
    //temp variable will represent value of the previous tile.
    //it will be set to 0 for each row
    //if the current element of the board isn't equal to temp and the value of current element isn't 0. Tiles are not a match, temp set to current element.
    //if temp is equal to current element, tiles are a match and we add their sum to the score
    //similar steps for each direction with difference in the manner in which we loop through the board.
    
    //for left direction
    if (move == 'a') {
        // search through board row by row from left to right
        for (int i = 0; i < size; i++) {
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
    // for right direction
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
    //for upward direction
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
    //for downward direction
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


// (check_finish) := Function to check if the game has finished.
// Game finishes when the board is full && there are no possible combinations left on the board
// If game finished, returns true. Else returns false.

bool check_finish(int size, vector<vector<int>> &board) {

    // Check if board is full by checking if any tile is 0.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                return false; // board is not full
            }
        }
    }
    // if reached here, board is full, need to check for combinations now (described below)

    // For combinations, vertical and horizontal checks need to be made.
    // Note: Left-to-right or right-to-left (likewise for vertical) does not matter.
    
    // *Explanation of logic*
    // Going from left-to-right (similar approach for top-to-down):
    // Variable 'target_sum' contains the sum that needs to be created if combination is present.
    // Variable 'current_sum' contains the current sum.
    // Loop through each row and iterate through each tile in each row.
    //      target_sum is 0 only until a non-zero tile is found in the row.
    //      when non-zero tile is found, target_sum = twice the value of the tile (needed for combination) and current_sum = value of tile
    //      if zero tile found, 
    //          continue in the loop, maintaining target_sum and current_sum
    //      if non-zero tile found again,
    //          add it to current_sum
    //          if current_sum == target_sum,
    //              combination is found
    //          if current_sum != target_sum (it means the non-zero tile is not the same as the previous non-zero tile found),
    //              target_sum is now changed to twice the new non-zero tile and current sum is the new non-zero tile
    // Loop
    // return false if no combination found


    // Checking horizontally (logic described above)
    for (int i = 0; i < size; i++) {
        
        int target_sum = 0;
        int current_sum = 0;
        
        for (int j = 0; j < size; j++) {
            if (target_sum == 0) {
            
                target_sum = board[i][j] * 2;
                current_sum = board[i][j];
            
            } else {
            
                current_sum += board[i][j];
            
                if (current_sum == target_sum) {
                    return false; // combination is present
                } else if (board[i][j] == 0) {
                    continue;
                } else {
                    target_sum = board[i][j] * 2;
                    current_sum = board[i][j];
                }
            }
        } 
    }

    // Checking vertically (logic described above)
    for (int i = 0; i < size; i++) {

        int target_sum = 0;
        int current_sum = 0;
        
        for (int j = 0; j < size; j++) {
            if (target_sum == 0) {
                
                target_sum = board[j][i] * 2;
                current_sum = board[j][i];
            
            } else {
                
                current_sum += board[j][i];
                
                if (current_sum == target_sum) {
                    return true; // combination is present
                } else if (board[j][i] == 0) {
                    continue;
                } else {
                    target_sum = board[j][i] * 2;
                    current_sum = board[j][i];
                }
            }
        } 
    }

    return false;
}
