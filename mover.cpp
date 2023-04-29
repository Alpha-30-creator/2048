#include "mover.h"

using namespace std;

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
