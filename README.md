# 2048+ // Group # 63

## Identification of team members:
Abdurrahman Saad - 3036094344 | 
Hannan Javed - 3036094320 |
Shah Jahan Ishaq - 3036095180 |
Yerdaulet Mussabek - 3036087157 |
Zuhayr Abdullazhanov - 3036056732

## Text-Based 2048 Game
This is a simple implementation of the popular 2048 game in C++, without any external libraries. The game is played on a text-based grid, with the player using arrow keys to move numbered tiles around the board and combine them. The goal is to reach the highest numbered tile possible, with a maximum value of 2048.

## Rules
The game begins with two tiles randomly placed on the board, with values of either 2 or 4. The player uses the arrow keys (up, down, left, right) to move all the tiles on the board in one direction. When two tiles with the same value collide, they merge into a single tile with their sum as the new value. The player's score increases with each merge.

If the player successfully combines two tiles to form a 2048 tile, they win the game. If the board is filled with tiles and there are no more moves available, the game is over.

## Levels
This implementation of 2048 includes three levels of difficulty:

- Easy: 3x3 grid
- Medium: 4x4 grid
- Hard: 5x5 grid

The larger grids provide more challenge and require more strategic thinking to achieve a high score.

## Leaderboard
After completing a game, the player's score is added to a leaderboard. The leaderboard displays the top five scores for each level, allowing players to compete against each other for the highest score. The leaderboard is stored locally and persists between game sessions.

## Running the Game
We hope you enjoy playing this text-based version of 2048!
## Compiling the game
## The main menu
After the game is compiled and executed, it asks the user to enter the username. After that, the main menu is displayed with four options:
1. New game
2. Load game
3. Instruction
4. Quit game
The New game will initialize the board and start a new game.
The Load game is to load any previously saved game (if the user has any) and initialize the board with the values. It will output no saved games if the user does not have any saved game.
Instruction will print the instructions of the game
Quit game is used to exit the game
## Starting a new game
After pressing one, a new game will be started and the following functions will be executed:
## Initializing the Board
The initialize_board function sets up the game board with a given size and populates it with two random tiles of numeric value 2. It does so by using a nested for loop and a random number generator to place the tiles randomly on the board.
## Making a move
The move function is the backbone of the program when the game is running. It takes the board, its size, and the player's desired move (up, down, left or right) as a parameter, and configures the values of the board based on the direction. It does so by iterating over the rows and colums of the board, and creating a new board which is modified based on the board values and direction.  If a move results in the combination of tiles, then a new tile with their sum is created and this is saved to the board. After combining tiles, the function shifts the remaining tiles with empty cells between them, or tiles with different values to the left or right, or up or down, depending on the direction of the move and it is also saved to the board.
## Clearing the Screen
The clear_screen function is an important feature of the game that is called after each move to clear the screen and keep the display clean. This function uses system-specific commands to clear the terminal window and display the updated game board. By clearing the screen after each move, the player can focus on the current state of the game board without being distracted by previous moves or cluttered displays. This improves the overall user experience and makes it easier for the player to keep track of their progress throughout the game
## Calculating Score
The calculate_score is called after the move function if the check finish returns a false, that is moves can still be made in the game and it is not over yet. This function takes the player's desired move (up, down, left, or right), the current score, the size of the board, and the current state of the board as input. It then calculates the score the player earns based on the tiles that are combined as a result of the move. The function uses a sliding window approach to check for valid combinations of adjacent cells that add up to twice the value of a single cell, and updates the score based on the sum of the combined tiles. The score is then displayed below the board with the display_score function.
## Generating Random Tiles
The generate_random_tile function generates a random tile of value 2 in an empty cell on the board after every successful move. The function first creates a vector of empty cells, selects a random empty cell, and assigns a value of 2 to that cell.
## Checking for Game Over
The check_finish function checks if the game is over. It returns true if the board is full and there are no possible combinations left on the board. The function iterates over the board twice, once horizontally and once vertically, using a sliding window approach to check for valid combinations of adjacent cells that add up to twice the value of a single cell.
## Reset Game
Our game includes a reset feature that allows the user to reset the game board at any stage of the game. To reset the board, the user "r" key. This will prompt a confirmation message asking if you are sure you want to reset the game. The board can be resetted to its initial state by pressing "1". If "r" was pressed accidentally, "2" can be pressed to not proceed with the reset. This feature provides a more user-friendly experience and enable the user to restart the game at any stage of the game.
## Coding features and functions
## Use of Standard Template Library
The game uses a 2D vector that contains the main status of the game when it is started after choosing the difficulty level. It's size depends on the user's input and can 3x3, 4x4 or 5x5 depending on the difficulty level.
## Updating the Leaderboard
A leaderboard file is present which contains scores of all users with a game that ended. It is sorted in terms of descending order of score, so the top score is the first line of the file and so on. The update_leaderboard function is responsible for updating the leaderboard after each game. It takes the player's score and the username as input, and updates the leaderboard file with the new score if it is among the top ten scores. It reads scores from the file and decides to update it based on the condition specified. An additional feature implemented in this function is to check if the user has beaten his previous high score. It checks if the current user already has a high score in the leaderboard, and if the new score is greater than the high score, it returns a true indiciating that the user has beaten his old high score, otherwise it will return false. This function uses file manipulation commands to read and write to the leaderboard file, ensuring that the leaderboard is updated accurately and reliably.
## Displaying the Leaderboard
The display_leaderboard function is responsible for displaying the contents of the leadboard file on the screen. It loops throught all the lines of the file, which can be at max ten, and displays them on the screen. This function is called after each game to allow players to see where they stand in the rankings and compete against other players for the highest scores.
## Saving the game
The save_game function allows the player to save the current state of the game and resume playing later. It takes the current state of the board, the current score, and the username as input, and writes them to the file named loadgame.txt. It saves it in the format <username><space><size><space><score><board values seperated by space>. Moreover it checks if the user already had a previous saved game, and overwrites the previous game board values with the new values if it is the case, otherwise it appends the game status to the end of the file.
## Loading the Game
The load_game function allows the player to resume playing a previously saved game. It reads the saved game file and reconstructs the game state, score, and level of difficulty, allowing the player to continue playing from where they left off. It takes the username and score (score passed by reference) as an input, and loops through all the lines in the file loadgame.txt to check if the user has a saved game. If it does it creates a new 2D vector board and saves the old game values to it and return it, otherwise outputs that the user has no saved game and exits.
## User Input Validation
Throughout the game, user input is validated to ensure that the player enters only valid moves, menu options, and difficulty levels. This validation is implemented at every stage of the game and ensures that the game runs smoothly and that the player only enters valid inputs. By validating user input, errors and unexpected behavior are prevented, providing a more enjoyable and user-friendly experience.
## Makefile
The game uses a makefile to automate the compilation and linking process. It specifies the compilation flags and dependencies for each target, allowing us to easily build and run our game with one command. By using a makefile, we ensure that our code is up-to-date and compiled accurately. The makefile also includes rules for cleaning up the project directory, ensuring that the project remains organized and easy to navigate.
## Header Files
The header files for the game contain function prototypes and other declarations that are used throughout the program. These files are included at the beginning of each source file and provide a way for the compiler to recognize the functions and variables used in the program. By using header files, the code is more organized and modular, making it easier to read and maintain. Additionally, header files allow for the separation of interface and implementation, enabling the program to be easily extended and modified.
