#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to initialize the board takes size of the board and the board itself as input and returns the 2D board.
void initializeBoard(int size, vector<vector<int>> &board) {
    // Resize the board with the given size and initialize its elements with 0
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
        int x = rand() % size;
        int y = rand() % size;
        board[x][y] = 2;
    }
}
