# ENGG1340 - Group #63
## Game: 2048

# Identification of team members:
Abdurrahman Saad - 
Zuhayr Abdullazhanov - 3036056732
Shah Jahan Ishaq -
Hannan Javed -
# Text-Based 2048 Game

This is a simple implementation of the popular 2048 game in C++, without any external libraries. The game is played on a text-based grid, with the player using arrow keys to move numbered tiles around the board and combine them. The goal is to reach the highest numbered tile possible, with a maximum value of 2048.
"""
+------+------+------+------+
|      |      |      |      |
|  2   |      |  4   |      |
|      |      |      |      |
+------+------+------+------+
|      |      |      |      |
|      |  8   |  2   |      |
|      |      |      |      |
+------+------+------+------+
|      |      |      |      |
|      |      |      |      |
|  4   |  2   |      |      |
+------+------+------+------+
|      |      |      |      |
|      |      |      |  4   |
|      |      |      |      |
+------+------+------+------+
"""

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
