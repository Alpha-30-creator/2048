#include "graphics.h"
#include "gameplay.h"
#include "color.h"
#include "fileManipulation.h"

#include <iostream>
#include <cstdlib> 

#ifdef _WIN32
#include <conio.h>
#define GET_CHAR() _getch()
#else
#include <termios.h>
#include <unistd.h>
#define GET_CHAR() ({ \
    char __c; \
    struct termios __old, __new; \
    tcgetattr(STDIN_FILENO, &__old); \
    __new = __old; \
    __new.c_lflag &= ~(ICANON | ECHO); \
    tcsetattr(STDIN_FILENO, TCSANOW, &__new); \
    __c = getchar(); \
    tcsetattr(STDIN_FILENO, TCSANOW, &__old); \
    if (__c == '\n') __c = '\r'; /* Return '\r' instead of '\n' */ \
    __c; \
})
#endif

using namespace std;

vector<vector<int>> board;
int size, score = 0;
string username;


// Pauses the program, press enter to continue
void pause() {
	cout << green << bold_on << "\n\nPress enter to continue..." << bold_off << def;
	char s = GET_CHAR();
	while (s != '\r') {
		s = GET_CHAR();
	}
	cout << '\n';
}

// This function takes input for user making move without waiting for the user to press Enter.
char instant_input_move() {
	cout << green << bold_on << "\nSWIPE TO MAKE MOVE... (W/A/S/D)" << bold_off << def << '\n';
	char c = tolower(GET_CHAR());
	while (c != 'w' && c != 'a' && c != 's' && c != 'd' && c != 'q' && c != 'r') {
		c = tolower(GET_CHAR());
	}
	return c;

}

// asks the user for the integer input
// returns the input of the user
// min_val - minimum value for the input
// max_val - maximum value for the input
// Error 1 - means input is out of boundaries
// Error 2 - input is not integer
int input(string message, int min_val, int max_val) {
	cout << green << bold_on << '\n' << message << bold_off << def << '\n';
	
	string s;
	cin >> s;
	int value = 0;
	for (char i : s) {
		if (i >= '0' && i <= '9') value = value * 10 + (i - '0');
		else {
			cout << red << bold_on << "[ERROR] Type again\n" << bold_off << def;
			return input(message, min_val, max_val);
		}
	}
	
	if (value >= min_val && value <= max_val) return value;
	else {
		cout << red << bold_on << "[ERROR] Type again\n" << bold_off << def;
		return input(message, min_val, max_val);
	}
}

// menu of the game
void menu() {
	clear_screen();

	print_menu(username);

	int menu_choice = input("Choose option (1-4):", 1, 4);

	clear_screen();

	if (menu_choice == 1) {
		print_difficulty_menu();

		int diff = input("Choose option (1-4):", 1, 4);

		if (diff == 4) {
			menu();
			return;
		}

		size = 6 - diff;

		initialize_board(size, board);
	}

	else if (menu_choice == 2) {
		board = load_game(username, score);
		size = board.size();
		if (board.empty()) {
			pause();
			menu();
		}
	}

	else if (menu_choice == 3) {
		clear_screen();

		print_instructions();

		pause();
		menu();
	}

	else if (menu_choice == 4) {
		exit(1);
		return;
	}
}

int main() {
	clear_screen();

	print_red_divider();
	print_title();
	print_red_divider();

	for (int i = 1; i <= 3; i++) cout << '\n';

	cout << green << bold_on << "Type your username:  " << bold_off << def;
	getline(cin, username);
	clear_screen();
	menu();

	while (1) {
		clear_screen();
		display_board(board);

		print_score(score);
		print_red_divider();

		if (check_finish(size, board)) {
			print_game_over();

			pause();
			clear_screen();
			if (update_leaderboard(score, username)) {
				string s = "Congratulations! You beat your highscore!";
				cout << yellow << bold_on << "\n" << get_chars_util(' ', 40 - s.length() / 2)<< s << bold_off << def << "\n\n";
			};
			display_leaderboard(get_leaderboard());
			pause();

			if (input("Do you want to play again? [1 - Yes. 2 - No]: ", 1, 2) == 1) {
				
				board.clear();
				score = 0;

				menu();

				continue;
			}

			else menu();
		}

		char dir;
		dir = instant_input_move();

		// If want to quit the game
		if (dir == 'q') {
			int choice = input("You pressed Q. Do you want to save and quit the game? [1 - Yes // 2 - No]: ", 1, 2);
			// Confirm quit
			if (choice == 1) {
				save_game(board, score, username);
				board.clear(); score = 0;
				pause();
				menu();
			} else if (choice == 2) { // Do not quit
				cout << green << bold_on << '\n' << "Please resume your play!" << bold_off << def << '\n';
				dir = instant_input_move();
			}
		} else if (dir == 'r') { // If want to reset the board
			int choice = input("You pressed R. Do you want to reset the board? [1 - Yes // 2 - No]: ", 1, 2);
			if (choice == 1) { // Confirm reset
				board.clear(); score = 0; initialize_board(size, board);
				clear_screen();
			} else if (choice == 2) { // do not reset
				cout << green << bold_on << '\n' << "Please resume your play!" << bold_off << def << '\n';
				dir = instant_input_move();
			}
		} else {
			calculate_score(dir, score, size, board);
			move(board, size, dir);
			generate_random_tile(size, board);
		}
	}

	return 0;
}
