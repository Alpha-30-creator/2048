// This is a header file for the graphics module of the 2048 game.
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>
using namespace std;

// Function declarations for the graphics module
string get_chars_util(char ch, int number_of_chars);
void print_title();
void print_red_divider();
void print_instructions();
void display_loading();
void display_board(svector<stdvector<int>>& board);
void print_menu(string username);
void print_difficulty_menu();
void display_leaderboard(vector<string> leader_board);
void clear_screen();
  
#endif
