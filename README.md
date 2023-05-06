# 2048+ // Group # 63

## Identification of team members:
| Member Name | University ID |
| --- | --- |
| Abdurrahman Saad | 3036094344 | 
| Hannan Javed | 3036094320 |
| Shah Jahan Ishaq | 3036095180 |
| Yerdaulet Mussabek | 3036087157 |
| Zuhayr Abdullazhanov | 3036056732|

## Text-Based 2048 Game
This is a simple implementation of the popular 2048 game in C++, without any external libraries. The game is played on a text-based grid, with the player using the wasd keys to move numbered tiles around the board and combine them. The goal is to reach the highest score by combining the same valued tiles!

## Rules
The game begins with two tiles randomly placed on the board, with values of 2. The player uses the wasd keys (up, down, left, right) to move all the tiles on the board in one direction. When two tiles with the same value collide, they merge into a single tile with their sum as the new value. The player's score increases with each merge.

The player can continue playing the game and merging tiles until there are no more valid moves available. When the board is completely filled with tiles and there are no more valid moves, the game is over.

We hope you enjoy playing this text-based version of 2048!

### Difficulty Levels
This implementation of 2048 includes three levels of difficulty:

- **Easy: 5x5 grid**
- **Medium: 4x4 grid**
- **Hard: 3x3 grid**

The smaller grids provide more challenge and require more strategic thinking to achieve a high score.

## Running the game
### Compilation
To compile the game, simply run the command `make` in the command prompt. Then to run the game, type `./main` and press enter. The game will be started!
If you want to start over with a clean slate, you can enter the command `make clean` to remove any previously compiled files.
### The main menu
After the game is compiled and executed, it asks the user to enter the username. After that, the main menu is displayed with four options:
1. New Game
   - This will ask the user to enter the difficulty level. It will then initialize the board with the size accordingly and start a new game.
2. Load game
   - This is used to load any previously saved game (if the user has any) and initialize the board with the values. It will output no saved games if the user does not have any saved game.
3. Instruction
   - This will print the instructions of the game.
4. Quit game
   - To quit the game
## Implementation details
The game is implemented using these key functions:

### Initializing the Board
The `initialize_board` function sets up the game board with a given size and populates it with two random tiles of numeric value 2. It does so by using a nested for loop and a random number generator to place the tiles randomly on the board.
### Making a move
The `move` function is the backbone of the program when the game is running. It takes the board, its size, and the player's desired move (up, down, left or right) as a parameter, and configures the values of the board based on the direction. It does so by iterating over the rows and colums of the board, and creating a new board which is modified based on the board values and direction.  If a move results in the combination of tiles, then a new tile with their sum is created and this is saved to the board. After combining tiles, the function shifts the remaining tiles with empty cells between them, or tiles with different values to the left or right, or up or down, depending on the direction of the move and it is also saved to the board.
### Clearing the Screen
The `clear_screen` function is an important feature of the game that is called after each move to clear the screen and keep the display clean. This function uses system-specific commands to clear the terminal window and display the updated game board. By clearing the screen after each move, the player can focus on the current state of the game board without being distracted by previous moves or cluttered displays. This improves the overall user experience and makes it easier for the player to keep track of their progress throughout the game.
### Calculating Score
The `calculate_score` is called after the move function if the check finish returns a false, that is moves can still be made in the game and it is not over yet. This function takes the player's desired move (up, down, left, or right), the current score, the size of the board, and the current state of the board as input. It then calculates the score the player earns based on the tiles that are combined as a result of the move. The function uses a sliding window approach to check for valid combinations of adjacent cells that add up to twice the value of a single cell, and updates the score based on the sum of the combined tiles. The score is then displayed below the board with the display_score function.
### Checking for Game Over
The `check_finish` function checks if the game is over. It returns true if the board is full and there are no possible combinations left on the board. The function iterates over the board twice, once horizontally and once vertically, using a sliding window approach to check for valid combinations of adjacent cells that add up to twice the value of a single cell.
### Leaderboard
After completing a game, the player's score is added to a leaderboard. The `display_leaderboard` function displays the top ten scores (for all levels), allowing players to compete against each other for the highest score. The leaderboard is stored locally and persists between game sessions.

## Gameplay features
In addition to the basic rules of the 2048 game, this implementation of the text-based 2048 game includes several features that enhance the gameplay experience:
Enhanced Gameplay Features

### Instant Input
To make the gameplay experience more responsive and fluid, the game has an instant input feature that eliminates the need for players to press enter after each move. With this feature, players can make moves quickly and efficiently, keeping the game's momentum going.
### User Input Validation
To ensure that players only enter valid moves, menu options, and difficulty levels, the game has a user input validation feature. This feature checks for input errors throughout the game, preventing unexpected behaviors and making the game more enjoyable and user-friendly.
### Reset Game
To enable players to start over at any point in the game, the game has a reset feature. By pressing the "r" key, players can reset the game board to its initial state. A confirmation message is displayed, asking players to confirm whether they want to proceed with the reset. This feature provides a more user-friendly experience and enables players to restart the game at any stage.
### Quit the Game
To allow players to exit the game quickly and easily, the game has a quit feature. By pressing the "q" key, players can end the game immediately. This feature is useful in situations where players need to attend to something else and don't want to lose their progress.
### Beat High Score
To add an extra level of challenge to the game, the game has a feature that checks if the player has beaten their previous high score. If the player's score is higher than their previous high score, they are notified of their achievement. This feature encourages players to push themselves and achieve their personal best.

These enhanced gameplay features make the game more responsive, user-friendly, and challenging. They demonstrate the developer's commitment to providing a high-quality gaming experience for players.
## Coding features and functions
To create a robust and efficient implementation of the text-based 2048 game, this game has incorporates several coding features and functions that enhance the game's functionality and performance:
### Use of Standard Template Library
The game uses a 2D vector from the standard template library of C++ that contains the main status of the game board when it is started after choosing the difficulty level. This data structure is used for storing the game status.
### Dynamic Memory Management
When the game is started, dynamic memory allocation is used to create the 2D vector that represents the game board. The size of the vector is determined by the user's choice of difficulty level, and it can be either 3x3, 4x4, or 5x5. This allocation of memory allows for the efficient use of resources, as the size of the vector is not statically defined, and it can be changed at runtime based on the user's input.
### Generating Random Tiles
The `generate_random_tile` function generates a random tile of value 2 in an empty cell on the board after every successful move. The function first creates a vector of empty cells, selects a random empty cell, and assigns a value of 2 to that cell. This completes the requirement of generating a random game set.
### Updating the Leaderboard
Th leaderboard file contains the top ten scores with username and is sorted in terms of descending order of score, so the top score is the first line of the file and so on. The `update_leaderboard` function is responsible for updating the leaderboard after each game. It takes the player's score and the username as input, and updates the leaderboard file with the new score if it is among the top ten scores. It reads scores from the file and decides to update it based on the condition specified. 
### Saving the game
The `save_game` function allows the player to save the current state of the game and resume playing later. It takes the current state of the board, the current score, and the username as input, and writes them to the file named loadgame.txt. It saves it in the format <username><space><size><space><score><board values seperated by space>. It can save game of multiple users with different usernames.
Moreover it checks if the user already had a previous saved game, and overwrites the previous game board values with the new values if it is the case, otherwise it appends the game status to the end of the file. This completes the requirement for having file input/output for saving game status.
### Loading the Game
The `load_game` function allows the player to resume playing a previously saved game. It reads the saved game file and reconstructs the game state, score, and level of difficulty, allowing the player to continue playing from where they left off. It takes the username and score (score passed by reference) as an input, and loops through all the lines in the file loadgame.txt to check if the user has a saved game. If it does it creates a new 2D vector board and saves the old game values to it and return it, otherwise outputs that the user has no saved game and exits.
### Multiple Source Code Files
This implementation of the text-based 2048 game uses multiple source code files to organize the code into logical and modular units. This completes the requirement of having program code in multiple files.
### Makefile
The game uses a makefile to automate the compilation and linking process. It specifies the compilation flags and dependencies for each target, allowing us to easily build and run our game with one command. By using a makefile, we ensure that our code is up-to-date and compiled accurately. The makefile also includes rules for cleaning up the project directory, ensuring that the project remains organized and easy to navigate.
### Header Files
The header files for the game contain function prototypes and other declarations that are used throughout the program. These files are included at the beginning of each source file and provide a way for the compiler to recognize the functions and variables used in the program. By using header files, the code is more organized and modular, making it easier to read and maintain. Additionally, header files allow for the separation of interface and implementation, enabling the program to be easily extended and modified.
