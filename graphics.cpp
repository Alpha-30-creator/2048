#include "color.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Utility function for printing a specific character a specific number of times
string get_chars_util(char ch, int number_of_chars) {
    string str = "";
    for (int i = 0; i < number_of_chars; i++) {
        str += ch;
    }
    return str;
}
// Function to display the current state of the board
void display_board(vector<vector<int>>& board) {
    int size = board.size();
    cout << "Current Board:\n\n";

    // Define ASCII escape codes for colored text
    const string red = "\033[0;31m";
    const string green = "\033[1;32m";
    const string yellow = "\033[1;33m";
    const string blue = "\033[1;34m";
    const string magenta = "\033[1;35m";
    const string cyan = "\033[1;36m";
    const string reset = "\033[0m";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Determine the color of the tile based on its value
            string color;
            switch (board[i][j]) {
                case 2:
                    color = green;
                    break;
                case 4:
                    color = magenta;
                    break;
                case 8:
                    color = yellow;
                    break;
                case 16:
                    color = cyan;
                    break;
                case 32:
                    color = blue;
                    break;
                default:
                    color = red;
                    break;
            }
            // Output the current tile with the appropriate color and padding
            cout << setw(6) << left << color << board[i][j] << reset;
        }
        cout << '\n';
    }
    cout << '\n';
}
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
// This function prints a bold red divider
void print_red_divider() {
    cout << bold_on;
    cout << red << get_chars_util('-', 80) << def << '\n';
    cout << bold_off;
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
// Output a message to let the user know that the game is being loaded
    cout << "Loading game...\n\n";
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
    print_red_divider();
    cout << bold_off;
}
// Function to display the difficulty level

void print_difficulty_menu() {
    string s = "  Difficulty  ";
    cout << bold_on;
    cout << red << get_chars_util('-', 40 - s.length() / 2) << green << s << red << get_chars_util('-', 40 - s.length() / 2) << def << "\n\n";
    cout << green;
    cout << "Please select a difficulty level:\n\n";
    cout << "1. Easy - 3x3 \n";
    cout << "2. Medium - 4x4 \n";
    cout << "3. Hard - 5x5 \n\n";
    cout << red << get_chars_util('-', 80) << def;
    cout << bold_off;
}

// Function to display the leaderboard
void display_leaderboard(int board[]) {
    // Output a header for the leaderboard display
    cout << "Leaderboard:\n\n";
    // Get the size of the leaderboard array
    int size = sizeof(board)/sizeof(board[0]);
    // Loop through each player in the leaderboard
    for (int i = 0; i < size; i++) {
        // Output the current player number and their score
        cout << "Player " << i+1 << ": " << board[i] << "\n";
    }
    // Output an additional newline character after the leaderboard display for spacing
    cout << '\n';
}


//function to clear the screen
void clear_screen() {
    system("clear");
}
