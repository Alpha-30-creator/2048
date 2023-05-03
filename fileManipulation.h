// fileManipulation.h
#ifndef FILEMANIPULATION_H
#define FILEMANIPULATION_H

#include <string>
#include <vector>
using namespace std;

void save_game(vector<vector<int>> board, int score, string username);
vector<vector<int>> load_game(string username, int &score);
vector<string> get_leaderboard();
bool update_leaderboard(int score, string username);

#endif
