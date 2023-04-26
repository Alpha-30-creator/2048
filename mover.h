#ifndef MOVER_H
#define MOVER_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

// function to move the board
// dir - direction (up, down, left, right)

void move(vector<vector<int>> &board, int size, string dir);

#endif
