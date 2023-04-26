#include "mover.h"

using namespace std;

void mover_update(vector<vector<int>> &board, int size, int x, int y, int dx, int dy) {
	int new_x = x + dx, new_y = y + dy;
	if (new_x < 1 || new_y < 1 || new_x > size || new_y > size) return;

	if (board[x][y] == board[new_x][new_y]) {
		board[x][y] *= 2;
		board[new_x][new_y] = 0;
	}
	else if (board[x][y] == 0) {
		board[x][y] = board[new_x][new_y];
		board[new_x][new_y] = 0;
	}

	mover_update(board, size, new_x, new_y, dx, dy);
}	

//check header file for instructions
void move(vector<vector<int>> &board, int size, string dir) {
	for (char &i : dir) {
		i = tolower(i);
	}

	if (dir == "left") {
		for (int i = 1; i <= size; i++) {
			mover_update(board, size, i, 1, 0, 1);
		}
	}
	
	if (dir == "right") {
		for (int i = 1; i <= size; i++) {
			mover_update(board, size, i, size, 0, -1);
		}
	}

	if (dir == "up") {
		for (int i = 1; i <= size; i++) {
			mover_update(board, size, 1, i, 1, 0);
		}
	}

	if (dir == "down") {
		for (int i = 1; i <= size; i++) {
			mover_update(board, size, size, i, -1, 0);
		}
	}
}
