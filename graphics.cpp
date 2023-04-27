#include "color.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

// Function to print the title of the game when the game is run.
void print_title() {
    string title_card_2048 = R"(


    /\\\\\\\\\          /\\\\\\\                /\\\         /\\\\\\\\\
    /\\\///////\\\      /\\\/////\\\            /\\\\\       /\\\///////\\\
    \///      \//\\\    /\\\    \//\\\         /\\\/\\\      \/\\\     \/\\\
               /\\\/    \/\\\     \/\\\       /\\\/\/\\\      \///\\\\\\\\\/
              /\\\//      \/\\\     \/\\\     /\\\/  \/\\\       /\\\///////\\\
             /\\\//         \/\\\     \/\\\   /\\\\\\\\\\\\\\\\   /\\\      \//\\\
            /\\\/            \//\\\    /\\\   \///////////\\\//   \//\\\      /\\\
            /\\\\\\\\\\\\\\\   \///\\\\\\\/              \/\\\      \///\\\\\\\\\/
            \///////////////      \///////                \///         \/////////)";
    cout << green << bold_on << title_card_2048 << bold_off << def; // Using color definitions from color.h header file
    cout << "\n\n\n";
}

// Utility function for printing a specific character a specific number of times
string get_chars_util(char ch, int number_of_chars) {
    string str = "";
    for (int i = 0; i < number_of_chars; i++) {
        str += ch;
    }
    return str;
}

// Function to print game instructions
void print_instructions() {
    cout << "Instructions: \n";
    cout << "Use the arrow keys to move the tiles. When two tiles with the same number touch, they merge into one!\n";
    cout << "In this game, the player must combine tiles containing the same numbers until they reach the number 2048.\n";
    cout << "The tiles can contain only integer values starting from 2, and that are a power of two, like 2, 4, 8, 16, 32, and so on.\n";
    cout << "Ideally, the player should reach the 2048 tile within the smallest number of steps.\n";
    cout << "The board has dimension of 4 x 4 tiles, so that it can fit up to 16 tiles.\n";
    cout << "If the board is full, and there is no possible move to make like merging tiles together - the game is over.\n\n";
}
// Function to display loading message
void display_loading() {
    cout << "Loading game...\n\n";
// Function to display the current state of the board
void display_board(vector<vector<int>>& board) {
    int size = board.size();
    cout << "Current Board:\n\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(5) << board[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}
}
// This function also uses the color codes defined in color.h header file and uses the utility function get_chars_util to print character
void print_menu(string username) {
    int width = 80;
    string s = "  Menu  ";
    cout << bold_on;
    cout << red << get_chars_util('-', 40 - s.length() / 2) << green << s << red << get_chars_util('-', 40 - s.length() / 2) << def << "\n\n";
    cout << green;
    s = "Welcome, " + username;
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << "\n\n";
    s = "1. New Game";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << '\n';
    s = "2. Load Game";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << '\n';
    s = "3. Instructions";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << "\n\n";
    cout << def;
    cout << red << get_chars_util('-', 80) << def;
    cout << bold_off;
}
