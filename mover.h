#ifndef MOVER_H
#define MOVER_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;
// function to move the board
// a - board
// n - size
// dir - direction (up, down, left, right)

void move(vector<vector<int>> &a, int n, string dir);

#endif
