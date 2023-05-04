# ENGG1340 - Group #63
## Game: 2048

# Identification of team members:
Abdurrahman Saad - 
Zuhayr Abdullazhanov - 3036056732
Shah Jahan Ishaq -
Hannan Javed -
# Text-Based 2048 Game

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
## --------------------------------------------------------------------------------------------------------

## Initializing the Board
The initialize_board function sets up the game board with a given size and populates it with two random tiles of numeric value 2. It does so by using a nested for loop and a random number generator to place the tiles randomly on the board.
## Calculating Score
The calculate_score function takes the player's desired move (up, down, left, or right), the current score, the size of the board, and the current state of the board as input. It then calculates the score the player earns based on the tiles that are combined as a result of the move. The function uses a sliding window approach to check for valid combinations of adjacent cells that add up to twice the value of a single cell, and updates the score based on the sum of the combined tiles.
## Generating Random Tiles
The generate_random_tile function generates a random tile of value 2 in an empty cell on the board after every successful move. The function first creates a vector of empty cells, selects a random empty cell, and assigns a value of 2 to that cell.
## Checking for Game Over
The check_finish function checks if the game is over. It returns true if the board is full and there are no possible combinations left on the board. The function iterates over the board twice, once horizontally and once vertically, using a sliding window approach to check for valid combinations of adjacent cells that add up to twice the value of a single cell.
## Moving Tiles
The move function takes the current state of the board, its size, and the player's desired move (up, down, left or right) as input and updates the board based on the move. It iterates over the rows or columns of the board, depending on the direction of the move, and combines adjacent tiles if their values are equal. If a move results in the combination of tiles, the score is updated accordingly. After combining tiles, the function also shifts the remaining tiles to the left or right, or up or down, depending on the direction of the move.
