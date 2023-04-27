#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>

void initializeBoard(int size, std::vector<std::vector<int>> &board);
void calculateScore(char move, int &score, int size, std::vector<std::vector<int>> &board);
void generate_random_tile(int size, std::vector<std::vector<int>> &board);
bool check_finish(int size, std::vector<std::vector<int>> &board);

#endif