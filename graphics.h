// This is a header file for the graphics module of the 2048 game.
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>
// Function declarations for the graphics module
void print_title();
void print_red_divider();
void print_instructions();
void display_loading();
void display_board(std::vector<std::vector<int>>& board);
void print_menu(std::string username);
void clear_screen();
  
#endif
