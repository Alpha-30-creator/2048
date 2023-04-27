#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>

void print_title();
void print_instructions();
void display_loading();
void display_board(std::vector<std::vector<int>>& board);
void print_menu(std::string username);

#endif