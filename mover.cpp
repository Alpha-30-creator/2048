#include "mover.h"

using namespace std;

void mover_update(vector<vector<int>> &a, int n, int x, int y, int dx, int dy) {
	int new_x = x + dx, new_y = y + dy;
	if (new_x < 1 || new_y < 1 || new_x > n || new_y > n) return;

	if (a[x][y] == a[new_x][new_y]) {
		a[x][y] *= 2;
		a[new_x][new_y] = 0;
	}
	else if (a[x][y] == 0) {
		a[x][y] = a[new_x][new_y];
		a[new_x][new_y] = 0;
	}

	mover_update(a, n, new_x, new_y, dx, dy);
}	


void move(vector<vector<int>> &a, int n, string dir) {
	for (char &i : dir) {
		i = tolower(i);
	}

	if (dir == "left") {
		for (int i = 1; i <= n; i++) {
			mover_update(a, n, i, 1, 0, 1);
		}
	}
	
	if (dir == "right") {
		for (int i = 1; i <= n; i++) {
			mover_update(a, n, i, n, 0, -1);
		}
	}

	if (dir == "up") {
		for (int i = 1; i <= n; i++) {
			mover_update(a, n, 1, i, 1, 0);
		}
	}

	if (dir == "down") {
		for (int i = 1; i <= n; i++) {
			mover_update(a, n, n, i, -1, 0);
		}
	}
}
