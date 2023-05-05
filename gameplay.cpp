#include "gameplay.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

// Function to initialize the board
// Inputs: integer size of the board & 2D vector for board (PASS-BY-REFERENCE).
// Outputs: Modifies the board within the function.
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

// Function to calculate the score of the board after a move.
// INPUTS: The move made by the user, the current score (PASS-BY-REFERENCE), the size of the board, 2D vector board
// OUTPUTS: Modifies the score within the function.
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

// Function to generate a random 2-tile after every move is done.
// Inputs: (i) integer size of the board, (ii) 2D vector of the current board as "pass-by-reference".
// Outputs: Nothing. It modifies the board within the function.
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
    if (num_of_empty_tiles > 0) {
        // Seed the random number generator
        srand(time(0));

        // Select a random index number in the vector, thereby selecting a random coordinate from the tiles.
        int random_array_index = rand() % num_of_empty_tiles;
        pair<int, int> random_pair = *(empty_tiles.begin() + random_array_index);
        //assign random empty tile with value 2
        board[random_pair.first][random_pair.second] = 2;
    }
}


// (check_finish) := Function to check if the game has finished.
// Inputs: (i) integer size of the board, (ii) 2D vector for the current state of board.
// Outputs: A boolean value indicating if the game is finished or not. If finished, return true. If not, return false.
bool check_finish(int size, vector<vector<int>> board) {

    // Check if board is full by checking if any tile is 0.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                return false; // board is not full
            }
        }
    }

    /* 
        Now check for combinations (logic described below)
        *Explanation of logic*
        The code checks if the game is finished or not by looking for any valid combinations of adjacent cells that add up to
        twice the value of a single cell. If such combinations exist, the game is not finished yet, and the function should return
        true. If no such combinations exist, the game is finished, and the function should return false.

        It iterates through the board twice, once horizontally and once vertically, using a sliding window approach to check for
        valid combinations of adjacent cells. The sliding window approach is efficient because it avoids the need to iterate through
        all possible combinations of cells, and it allows the code to quickly identify valid combinations.
    */


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



/*
	moves all the tiles to left, right, down, or up
	board - 2d vector that stores the game board
	size - the dimension of the game board
	dir - direction of the move ('w', 'a', 's', 'd')
	
	makes changes to the 2d vector directly
*/
	
void move(vector<vector<int>> &board, int size, char dir) {

	if (dir == 'a' || dir == 'd') {
		
		
		for (int i = 0; i < size; i++) { // iterate over all rows
			vector<int> new_row;
	
			/*
				create a new empty vector for each row
				pushes all the non-zero values from the row to this vector
				during the pushing process, if the value of the current tile equals to the last element in the vector, then they merge
			*/
			
			if (dir == 'a') {
				for (int j = 0; j < size; j++) {
					if (board[i][j] == 0) continue;

					if (new_row.empty() == 0 && new_row.back() == board[i][j]) new_row[new_row.size() - 1] *= 2;
					else new_row.push_back(board[i][j]); 
				}
			}

			/*
				if direction is right, apply same solution as for left but with opposite iteration and reverse the vector at the end
			*/
			
			if (dir == 'd') {
				for (int j = size - 1; j >= 0; j--) {

					if (board[i][j] == 0) continue;

					if (new_row.empty() == 1) new_row.push_back(board[i][j]);
					else if (new_row.back() == board[i][j]) new_row[new_row.size() - 1] *= 2;
					else new_row.push_back(board[i][j]);
				}
			}
			
			new_row.resize(size, 0); 
           		if (dir == 'd') reverse(new_row.begin(), new_row.end());  

			board[i] = new_row;
		}


	}

	if (dir == 'w' || dir == 's') {
		
		for (int j = 0; j < size; j++) { // iterate over all columns
			vector<int> new_col;

			// the logick applies for up and down movements, but now we iterate over each column instead of rows
			
			if (dir == 'w') {
				for (int i = 0; i < size; i++) {
					if (board[i][j] == 0) continue;

					if (new_col.empty()) new_col.push_back(board[i][j]);
					else if (new_col.back() == board[i][j]) new_col[new_col.size() - 1] *= 2;
					else new_col.push_back(board[i][j]);
				}
			}

			if (dir == 's') {
				for (int i = size - 1; i >= 0; i--) {
					if (board[i][j] == 0) continue;

					if (new_col.empty()) new_col.push_back(board[i][j]);
					else if (new_col.back() == board[i][j]) new_col[new_col.size() - 1] *= 2;
					else new_col.push_back(board[i][j]);
				}
			}
		
			new_col.resize(size, 0);
			if (dir == 's') reverse(new_col.begin(), new_col.end());

			for (int i = 0; i < size; i++) {
				board[i][j] = new_col[i];
			}
			
		}
	}

}

