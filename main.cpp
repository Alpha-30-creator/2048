#include "graphics.h"
#include "gameplay.h"
#include "color.h"
#include "fileManipulation.h"

#include <iostream>
#include <cstdlib> 

#ifdef _WIN32
	#include <conio.h>
	// Pauses the program, press SPACEBAR to continue
	void pause_util() {
		cout << green << bold_on << "\n\nPress SPACEBAR to continue..." << bold_off << def;
		char s = _getch();
		while (s != ' ') {
			s = _getch();
		}
		cout << '\n';
	}
	// This function takes input for user making move without waiting for the user to press Enter.
	char instant_input_move() {
		cout << green << bold_on << "\nSWIPE TO MAKE MOVE... (W/A/S/D)" << bold_off << def << '\n';
		char c = tolower(_getch());
		while (c != 'w' && c != 'a' && c != 's' && c != 'd' && c != 'q' && c != 'r') {
			c = tolower(_getch());
		}
		return c;
	}
#else
	#include <termios.h>
	#include <unistd.h>

	void configure_terminal(struct termios &old_termios, struct termios &new_termios) {

		tcgetattr(STDIN_FILENO, &old_termios);
		new_termios = old_termios;
		new_termios.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	}

	void restore_terminal(struct termios &old_termios) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	}
	// Pauses the program, press SPACEBAR to continue
	void pause_util() {
		struct termios old_termios, new_termios;
		configure_terminal(old_termios, new_termios);
		cout << green << bold_on << "\n\nPress SPACEBAR to continue..." << bold_off << def;
		char s = cin.get();
		while (s != ' ') {
			s = cin.get();
		}
		restore_terminal(old_termios);
		cout << '\n';
	}

	// This function takes input for user making move without waiting for the user to press Enter.
	char instant_input_move() {
		struct termios old_termios, new_termios;
		configure_terminal(old_termios, new_termios);
		cout << green << bold_on << "\nSWIPE TO MAKE MOVE... (W/A/S/D)" << bold_off << def << '\n';
		char c = tolower(cin.get());
		while (c != 'w' && c != 'a' && c != 's' && c != 'd' && c != 'q' && c != 'r') {
			c = tolower(cin.get());
		}
		restore_terminal(old_termios);
		return c;
	}
#endif

using namespace std;

vector<vector<int>> board;
int size, score = 0;
string username;




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
			pause_util();
			menu();
		}
	}

	else if (menu_choice == 3) {
		clear_screen();

		print_instructions();

		pause_util();
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

			pause_util();
			clear_screen();
			if (update_leaderboard(score, username)) {
				string s = "Congratulations! You beat your highscore!";
				cout << yellow << bold_on << "\n" << get_chars_util(' ', 40 - s.length() / 2)<< s << bold_off << def << "\n\n";
			};
			display_leaderboard(get_leaderboard());
			pause_util();

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
				pause_util();
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
