#include "color.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

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
// This function also uses the color codes defined in color.h header file and uses the utility function get_chars_util to print character
void print_instructions() {
    string s = "  Instructions  ";
    cout << bold_on;
    cout << red << get_chars_util('-', 40 - s.length() / 2) << green << s << red << get_chars_util('-', 40 - s.length() / 2) << def << "\n\n";
    cout << green;
    cout << "Conventionally, in this game, the player must combine tiles containing the same\nnumbers until they reach the number 2048.\n";
    cout << "However, in this version, the player must keep combining tiles until it is no\nlonger possible.";
    cout << "The goal is to accumulate the highest score possible!\n";
    cout << "In order to combine the tiles the player can shift the tiles on the board\n up, left, down or right.\n";
    cout << " This is represented by the w, a, s and d keys on the keyboard.\n";
    cout << "The tiles can contain only integer values starting from 2, and that are\na power of two, like 2, 4, 8, 16, 32, and so on.\n";
    cout << "If the board is full, and there is no possible move to make like merging\ntiles together - the game is over.\n\n";
    cout << red << get_chars_util('-', 80) << def;
    cout << bold_off;
}

// Function to display loading message
void display_loading() {
    cout << "Loading game...\n\n";
}

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

//Function to print main menu
// This function also uses the color codes defined in color.h header file and uses the utility function get_chars_util to print character
void print_menu(string username) {
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
    cout << red << get_chars_util('-', 80) << def << "\n\n";
    cout << bold_off;
}
