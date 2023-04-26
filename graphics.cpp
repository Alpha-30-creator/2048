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

// Function to print menu for the player when game is started
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