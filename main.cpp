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
	cout << "\n\nPress enter to continue...";
	char s = GET_CHAR();
	while (s != '\r') {
		s = GET_CHAR();
	}
	cout << '\n';
}

// asks the user for the integer input
// returns the input of the user
// min_val - minimum value for the input
// max_val - maximum value for the input
// Error 1 - means input is out of boundaries
// Error 2 - input is not integer


// This function takes input without waiting for the user to press Enter.

char instant_input_move() {
	cout << "SWIPE TO MAKE MOVE... (W/A/S/D)" << '\n';
	char c = tolower(GET_CHAR());
	while (c != 'w' && c != 'a' && c != 's' && c != 'd') {
		c = tolower(GET_CHAR());
	}
	return c;

}

int input(string message, int min_val, int max_val) {
	cout << message << '\n';
	
	string s;
	cin >> s;
	int value = 0;
	for (char i : s) {
		if (i >= '0' && i <= '9') value = value * 10 + (i - '0');
		else {
			cout << "Error 2. Type again\n";
			return input(message, min_val, max_val);
		}
	}
	
	if (value >= min_val && value <= max_val) return value;
	else {
		cout << "Error 1. Type again\n";
		return input(message, min_val, max_val);
	}
}

// menu of the game
void menu() {
	clear_screen();

	print_menu(username);

	int menu_choice = input("Choose option (1-3):", 1, 3);

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
		menu();
		return;
	}
}

int main() {
	clear_screen();

	print_title();

	for (int i = 1; i <= 3; i++) cout << '\n';

	cout << "Type your username:\n";
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
			display_leaderboard(get_leaderboard());
			pause();

			if (input("Do you want to save the game [1 - Yes. 2 - No]: ", 1, 2) == 1) save_game(board, score, username);
			
			pause();

			if (input("Do you want to play again? [1 - Yes. 2 - No]: ", 1, 2) == 1) {
				
				board.clear();
				score = 0;

				menu();

				continue;
			}

			else break;
		}

		char dir;
		dir = instant_input_move();

		calculate_score(dir, score, size, board);
		move(board, size, dir);
		generate_random_tile(size, board);
	}

	return 0;
}
