#include "gameplay.h"
#include "graphics.h"
#include <vector>

using namespace std;

int main() {

    vector<vector<int>> board;
    int size = 4;
    initializeBoard(size, board);
    display_board(board);

    return 0;
}