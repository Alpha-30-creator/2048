#include "color.h"
#include "graphics.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    (get_chars_util) := This function is a utility function for display_board
    Inputs: char ch, int number_of_chars (both passed by value)
    Outputs: string
    Purpose: This function returns a string of characters
    Logic:
        1. Initialize a string str to empty string
        2. Iterate from 0 to number_of_chars
            2.1 Append ch to str
        3. Return str
*/
string get_chars_util(char ch, int number_of_chars) {
    string str = "";
    for (int i = 0; i < number_of_chars; i++) {
        str += ch;
    }
    return str;
}

/*
    (print_red_divider) := This function is a utility function for display_board
    Inputs: none
    Outputs: void
    Purpose: This function prints a red divider
*/
void print_red_divider() {
    cout << bold_on;
    cout << red << get_chars_util('-', 80) << def << '\n';
    cout << bold_off;
}

/*
    (print_row_border) := This function is a utility function for display_board
    Inputs: int size (passed by value)
    Outputs: void
    Purpose: This function prints the border of a row
*/
void print_row_border(int size) {
    cout << '\n' << get_chars_util(' ', 4*20/size);
    cout << red << "+";
    for (int i = 0; i < size; i++) {
        cout << red << setfill('-') << setw(9) << "" << setfill(' ') << "+" << def;
    }
    cout << '\n';
}

/*
    (display_board) := This function is used to display the board
    Inputs: vector<vector<int>>& board (passed by reference)
    Outputs: void
    Purpose: This function displays the board
    Logic:
        1. Get the size of the board
        2. Iterate from 0 to size of board
            2.1 Print the upper border of the row
            2.2 Print the empty row above tile value
            2.3 Print the row containing tile value
            2.4 Print the empty row below tile value
            2.5 Print the lower border of the row
*/
void display_board(vector<vector<int>>& board) {
    int rowSize = board.size();
    int colSize = board[0].size();
    cout << '\n' << bold_on;
    // upper border of table
    print_row_border(colSize);

    for (int i = 0; i < rowSize; ++i) {

        // empty row above tile value
        cout << get_chars_util(' ', 4*20/rowSize) << red << "|" << def;
        for (int j = 0; j < colSize; ++j) {
            cout << red << setw(5) << "" << setw(4) << "" << "|" << def;
        }
        cout << endl;

        // row containing tile value
        cout << get_chars_util(' ', 4*20/rowSize);
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
        cout << endl << get_chars_util(' ', 4*20/rowSize) << red << "|" << def;
        for (int j = 0; j < colSize; ++j) {
            cout << red << setw(5) << "" << setw(4) << "" << "|" << def;
        }

        // lower border of row
        print_row_border(colSize);
    }
    cout << bold_off;
}

/*
    (print_title) := This function is used to print the title card
    Inputs: void
    Outputs: void
    Purpose: This function prints the title card
*/
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


/*
    (print_instructions) := This function is used to print the instructions
    Inputs: void
    Outputs: void
    Purpose: This function prints the instructions
*/
void print_instructions() {
    string s = "  Instructions  ";
    cout << bold_on;
    cout << red << get_chars_util('-', 40 - s.length() / 2) << green << s << red << get_chars_util('-', 40 - s.length() / 2) << def << "\n\n";
    cout << green;
    s = get_chars_util(' ', 10) + "* GOAL: Accumulate the highest score possible by combining tiles of the same value. The sky is the limit! In order to combine the tiles, the player can shift the tiles on the board UP, LEFT, DOWN or RIGHT.\n\n" + get_chars_util(' ', 10) + "* CONTROLS: Use the W, A, S, and D keys on the keyboard to move the tiles. The tiles can contain only integer values starting from 2, and that are a power of two, like 2, 4, 8, 16, 32, and so on.\n\n" + get_chars_util(' ', 10) + "* ENDING: If the board is full, and there is no possible move to merge like tiles together - the game is over.\n\n" + get_chars_util(' ', 10) + "* SAVE/QUIT/RESET: Save and quit the game at any time by pressing the Q key. Or reset the board by pressing the R key.\n\n" + get_chars_util(' ', 10) + "* LOAD GAME: Load your last saved game by choosing the option from the Main Menu.\n\n";

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


/*
    (print_menu) := This function is used to print the menu
    Inputs: string username
    Outputs: void
    Purpose: This function prints the menu
*/
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
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << "\n";
    s = "4. Quit Game";
    cout << get_chars_util(' ', 40 - s.length() / 2) << s << "\n\n";
    cout << def;
    print_red_divider();
    cout << bold_off;
}

/*
    (print_difficulty_menu) := This function is used to print the difficulty menu
    Inputs: void
    Outputs: void
    Purpose: This function prints the difficulty menu
*/
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

/*
    (print_board) := This function is used to print the board
    Inputs: vector<vector<int>> board
    Outputs: void
    Purpose: This function prints the board
*/
void print_score(int score) {
    string s = "  Score: " + to_string(score) + "  ";
    cout << def << bold_on;
    cout << cyan; 
    cout << '\n' << get_chars_util('~', 40 - s.length() / 2) << s << get_chars_util('~', 40 - s.length() / 2) << "\n\n";
    cout << bold_off << def;
}

/*
    (print_game_pver) := This function prints the game over screen
    Inputs: none
    Outputs: void
    Purpose: This function prints the game over screen
*/
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

/*
    (display_leaderboard) := This function is used to display the leader board
    Inputs: vector<string> leader_board
    Outputs: void
    Purpose: This function displays the leader board
*/
void display_leaderboard(vector<string> leader_board) {
    string s = "  Leader Board  ";
    cout << bold_on;
    cout << yellow << "\n\n" << get_chars_util('*', 40 - s.length() / 2) << green << s << yellow << get_chars_util('*', 40 - s.length() / 2) << def << "\n\n";
    cout << green;
    //loop through vector and print all lines of leader board
    for (int i = 1; i <= leader_board.size(); i++) { 
        if (i == 1) cout << lightYellow;
        if (i == 2) cout << magenta;
        if (i == 3) cout << cyan;
        if (i > 3) cout << green;
        cout << setw(33) << i << ". ";
        cout << leader_board[i - 1] << endl;     
    }
    cout << '\n';
    cout << yellow << get_chars_util('*', 80) << def << '\n';
    cout << bold_off;
    cout << def;
}

/*
    (clear_screen) := This function is used to clear the screen
    Inputs: void
    Outputs: void
    Purpose: This function clears the screen
*/
void clear_screen() {
    system("clear");
}
