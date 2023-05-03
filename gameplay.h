// gameplay.h
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <string>
#include <vector>
using namespace std;

void initialize_board(int size, vector<vector<int>> &board);
void calculate_score(char move, int &score, int size, vector<vector<int>> &board);
void generate_random_tile(int size, vector<vector<int>> &board);
bool check_finish(int size, vector<vector<int>> board);
void move(vector<vector<int>> &board, int size, string dir);

#endif
