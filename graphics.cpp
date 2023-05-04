#include "color.h"
#include "graphics.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Utility function for printing a specific character a specific number of times
string get_chars_util(char ch, int number_of_chars) {
    string str = "";
    for (int i = 0; i < number_of_chars; i++) {
        str += ch;
    }
    return str;
}

// This function prints a bold red divider
void print_red_divider() {
    cout << bold_on;
    cout << red << get_chars_util('-', 80) << def << '\n';
    cout << bold_off;
}

// This function is a utility function for display_board
void print_row_border(int size) {
    cout << '\n' << get_chars_util(' ', 20);
    cout << red << "+";
    for (int i = 0; i < size; i++) {
        cout << red << setfill('-') << setw(9) << "" << setfill(' ') << "+" << def;
    }
    cout << '\n';
}

// Function to display the current state of the board
void display_board(vector<vector<int>>& board) {
    int rowSize = board.size();
    int colSize = board[0].size();
    cout << '\n' << bold_on;
    // upper border of table
    print_row_border(colSize);

    for (int i = 0; i < rowSize; ++i) {

        // empty row above tile value
        cout << get_chars_util(' ', 20) << red << "|" << def;
        for (int j = 0; j < colSize; ++j) {
            cout << red << setw(5) << "" << setw(4) << "" << "|" << def;
        }
        cout << endl;

        // row containing tile value
        cout << get_chars_util(' ', 20);
        cout << red << "|" << def;
        for (int j = 0; j < colSize; ++j) {
            //if value is 0 print empty cell as 0 represents empty cell
            if (board[i][j] == 0) {
                cout << red << setw(5) << "" << setw(4) << "" << "|" << def;
            } else {
                cout << green << setw(5) << board[i][j] << setw(4) << "" << red << "|";
            }
        }

        // empty row below the tile value 
        cout << endl << get_chars_util(' ', 20) << red << "|" << def;
        for (int j = 0; j < colSize; ++j) {
            cout << red << setw(5) << "" << setw(4) << "" << "|" << def;
        }

        // lower border of row
        print_row_border(colSize);
    }
    cout << bold_off;
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


// Function to print game instructions
// This function also uses the color codes defined in color.h header file and uses the utility function get_chars_util to print character
void print_instructions() {
    string s = "  Instructions  ";
    cout << bold_on;
    cout << red << get_chars_util('-', 40 - s.length() / 2) << green << s << red << get_chars_util('-', 40 - s.length() / 2) << def << "\n\n";
    cout << green;
    s = get_chars_util(' ', 10) + "* GOAL: Accumulate the highest score possible by combining tiles of the same value. The sky is the limit! In order to combine the tiles, the player can shift the tiles on the board UP, LEFT, DOWN or RIGHT.\n\n" + get_chars_util(' ', 10) + "* CONTROLS: Use the W, A, S, and D keys on the keyboard to move the tiles. The tiles can contain only integer values starting from 2, and that are a power of two, like 2, 4, 8, 16, 32, and so on.\n\n" + get_chars_util(' ', 10) + "* ENDING: If the board is full, and there is no possible move to merge like tiles together - the game is over.\n\n" + get_chars_util(' ', 10) + "* SAVE/QUIT: Save the game at any time by pressing the ___ key. Or quit the game without saving by pressing the ____ key.\n\n" + get_chars_util(' ', 10) + "* LOAD GAME: Load your last saved game by choosing the option from the Main Menu.\n\n";

    const int line_length = 60;
    int count = 0;
    string word;
    for (char c : s) {
        if (c == ' ' || c == '\n') {
            if (count + word.size() + 1 > line_length) {
                cout << '\n';
                cout << get_chars_util(' ', 10);
                count = 0;
            }
            cout << word << c;
            if (c == '\n') {
                count = 0;
            } else {
                count += word.size() + 1;
            }
            word.clear();
        } else {
            word += c;
        }
    }
    if (count + word.size() > line_length) {
        cout << '\n';
    }
    cout << word;

    print_red_divider();
    cout << bold_off;
}

// Function to display loading s
void display_loading() {
// Output a s to let the user know that the game is being loaded
    cout << "Loading 2048 game...\n\n";
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
    s = "Please select a difficulty level:";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << "\n\n";
    s = "1. Easy - 5x5";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << '\n';
    s = "2. Medium - 4x4";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << '\n';
    s = "3. Hard - 3x3";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << '\n';
    s = "4. Back to Main Menu";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << "\n\n";
    print_red_divider();
    cout << bold_off;
}

void print_score(int score) {
    string s = "  Score: " + to_string(score) + "  ";
    cout << def << bold_on;
    cout << cyan; 
    cout << '\n' << get_chars_util('~', 40 - s.length() / 2) << s << get_chars_util('~', 40 - s.length() / 2) << "\n\n";
    cout << bold_off << def;
}

void print_game_over() {
    string game_over = R"(
________  ________  _____ ______   _______           ________  ___      ___ _______   ________     
|\   ____\|\   __  \|\   _ \  _   \|\  ___ \         |\   __  \|\  \    /  /|\  ___ \ |\   __  \/    
/\ \  \___|\ \  \|\  \ \  \\\__\ \  \ \   __/|        \ \  \|\  \ \  \  /  / | \   __/|\ \  \|\  \/   
 /\ \  \  __\ \   __  \ \  \\|__| \  \ \  \_|/__       \ \  \\\  \ \  \/  / / \ \  \_|/_\ \   _  _\/  
 /\ \  \|\  \ \  \ \  \ \  \    \ \  \ \  \_|\ \       \ \  \\\  \ \    / /   \ \  \_|\ \ \  \\  \|/ 
   /\ \_______\ \__\ \__\ \__\    \ \__\ \_______\       \ \_______\ \__/ /     \ \_______\ \__\\ _\/ 
    /\|_______|\|__|\|__|\|__|     \|__|\|_______|        \|_______|\|__|/       \|_______|\|__|\|__|
    
    )";
    cout << red << bold_on << game_over << bold_off << def << "\n\n";
}

// Function to display the leaderboard
void display_leaderboard(vector<string> leader_board) {
    string s = " Leader Board ";
    cout << bold_on;
    cout << red << get_chars_util('-', 40 - s.length() / 2) << green << s << red << get_chars_util('-', 40 - s.length() / 2) << def << "\n\n";
    cout << green;
    //loop through vector and print all lines of leader board
    for (int i = 1; i <= leader_board.size(); i++) {
        cout << i << ". " << leader_board[i - 1] << endl;     
    }
    print_red_divider();
    cout << bold_off;
    cout << def;
}

//Function to clear the screen
void clear_screen() {
    system("clear");
}
