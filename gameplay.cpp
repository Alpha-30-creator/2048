#include "gameplay.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

// Function to initialize the board 
void initialize_board(int size, vector<vector<int>> &board) {
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
void calculate_score(char move, int &score, int size, vector<vector<int>> &board) {
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
// Inputs: (i) integer size of the board, (ii) 2D vector of the current board as "pass-by-reference".
// Outputs: Nothing. It modifies the board within the function.
// Note: A random tile is generated no matter what as long as the game is running (i.e. the game is not finished)
//      because after every successful move, the total number of filled tiles must decrease by at least.

void generate_random_tile(int size, vector<vector<int>> &board) {
    // Create a vector containing pairs of coordinates (i, j) of currently empty tiles
    vector<pair<int, int>> empty_tiles;
    
    // Find all empty tiles and store their coordinates (i, j) as 'pairs' in the empty_tiles vector. 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                empty_tiles.push_back(make_pair(i, j));
            }
        }
    }
    // Find number of empty tiles
    int num_of_empty_tiles = empty_tiles.size();
    // Seed the random number generator
    srand(time(0));

    // Select a random index number in the vector, thereby selecting a random coordinate from the tiles.
    int random_array_index = rand() % num_of_empty_tiles;
    pair<int, int> random_pair = *(empty_tiles.begin() + random_array_index);
    //assign random empty tile with value 2
    board[random_pair.first][random_pair.second] = 2;
}


// (check_finish) := Function to check if the game has finished.
// Inputs: (i) integer size of the board, (ii) 2D vector for the current state of board.
// Outputs: A boolean value indicating if the game is finished or not. If finished, return true. If not, return false. 
// Note: Game finishes when the board is full && there are no possible combinations left on the board

bool check_finish(int size, vector<vector<int>> board) {

    // Check if board is full by checking if any tile is 0.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                return false; // board is not full
            }
        }
    }

    // Now  check for combinations (logic described below)
    // *Explanation of logic*
    // The code checks if the game is finished or not by looking for any valid combinations of adjacent cells that add up to
    // twice the value of a single cell. If such combinations exist, the game is not finished yet, and the function should return
    // true. If no such combinations exist, the game is finished, and the function should return false.

    // It iterates through the board twice, once horizontally and once vertically, using a sliding window approach to check for
    // valid combinations of adjacent cells. The sliding window approach is efficient because it avoids the need to iterate through
    // all possible combinations of cells, and it allows the code to quickly identify valid combinations.


    // Checking horizontally (logic described above)
    for (int i = 0; i < size; i++) {
        int target_sum = 0;
        int current_sum = 0;
        for (int j = 0; j < size; j++) {
            if (target_sum == 0) {
                target_sum = board[i][j] * 2;
                current_sum = board[i][j];         
            } 
            else {
                current_sum += board[i][j];
                if (current_sum == target_sum) {
                    return false; // combination is present
                } 
                else if (board[i][j] == 0) {
                    continue;
                } 
                else {
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
                    return false; // combination is present
                } else if (board[j][i] == 0) {
                    continue;
                } 
                else {
                    target_sum = board[j][i] * 2;
                    current_sum = board[j][i];
                }
            }
        } 
    }

    return true;
}


// a recursion function that supposed to be used only by the move function
// mover_update is used to update (move each square) one row or a column till the end
// the function does not return any value. It makes changes to the 2D vector itself (the game board) 
// board - a 2d vector that stores the game board
// size - the dimension of the board (the board is square-shaped)
// x, y - indices of the square that is being updated (x - row, y - column)
// dx, dy - difference between the current location and the next one (new x/y = current x/y + difference x/y)

void mover_update(vector<vector<int>> &board, int size, int x, int y, int dx, int dy) {
	int new_x = x + dx, new_y = y + dy; 
	// (new_x, new_y) - the indices of the square that will try to merge with the current square (x, y)
	// for example, if direction of the move is left, then (new_x, new_y) is the square right to the current one (x, y) (i.e new_x = x, new_y = y + 1)
	// another example: if direction of the move is up, then (new_x, new_y) is the square below the curret one (x, y) (i.e new_x = x + 1, new_y = y)

	if (new_x < 1 || new_y < 1 || new_x > size || new_y > size) return;
	// if the indices of the square that will try to merge with the current one are out of boundary, then it means that the current square is the last one in the row/column.
	// since there is no more square to consider, stop the recurssion

	// for explanation, we will refer to the square that is trying to merge with the current one as next square

	if (board[x][y] == board[new_x][new_y]) {
		// if the values of the next square and the current square are equal, then they merge into one with a doubled value
		// the indices where the new doubled value is being stored is (x, y) 
		// for example, if the direction is left
		// then (new_x, new_y) is the square right to the current one (x, y)
		// if their values are equal, then square on the left doubles and square on the right becomes equal to zero
		
		// but to merge, square (x, y) has to be unable to merge with the previous square (for example, if the direction is left, then previous square is the square left to the current one) or last in the column/row
		// thats why we consider the squares in the reverse order
		// for example, if the direction is left
		// we start from the leftmost square
		// and then go to the rightmost
		// and on our way, we try to move each square to the left

		board[x][y] *= 2;
		board[new_x][new_y] = 0; 
	}
	else if (board[x][y] == 0) { 
		// another case is if the current square is empty
		// if the current square is empty, then the new square will move to the place of the current square


		board[x][y] = board[new_x][new_y];
		board[new_x][new_y] = 0;
	}

	// third case: if the value in the current square is not zero, and their values are not equal
	// then nothing happens

	// consider the next square
	mover_update(board, size, new_x, new_y, dx, dy);
}	


// function to move board
// does not return any value, makes changes directly to the 2d vector (the game board)
// board - 2d vector that stores the game board
// size - the dimension of the board (the board is square-shaped)
// dir - direction of the move (right, left, up, down) (not case-sensitive)
void move(vector<vector<int>> &board, int size, string dir) {
	for (char &i : dir) {
		i = tolower(i);
	} // converts the direction string to lower case

	if (dir == "left") {
		// if the direction is left
		// then we update the squares in each row from the leftmost to the rightmost (explanation is in the mover_update() function)

		for (int i = 1; i <= size; i++) { // index of the row
			mover_update(board, size, i, 1, 0, 1); // x = i, y = 1 (leftmost square in the i-th row) 
			// dx = 0, dy = 1
		}
	}
	
	if (dir == "right") {
		// if the direction is right
		// then we update the squares in each row from the rightmost to the leftmost (explanation is in the mover_update() function)

		for (int i = 1; i <= size; i++) { // the index of the column
			mover_update(board, size, i, size, 0, -1); // x = i, y = size (rightmost square)
			// dx = 0, dy  = -1
		}
	}

	if (dir == "up") {
		// if the direction is up
		// then we update the squres in each column from top to bottom


		for (int i = 1; i <= size; i++) { // the index of the row
			mover_update(board, size, 1, i, 1, 0); // x = 1, y = i (upmost square in the i-th column)
			// dx = 1, dy = 0
		}
	}

	if (dir == "down") {
		for (int i = 1; i <= size; i++) {
			mover_update(board, size, size, i, -1, 0); // x = size, y = i (downmost square in the i-th column)
			// dx = -1, dy = 0
		}
	}
}
