# Yahtzee Game Simulation

## Overview

This project is a C program that simulates the classic dice game, Yahtzee. It allows a single human player to compete against a computer-controlled AI opponent. The game involves rolling five dice, strategically choosing which dice to keep, and aiming to score points by forming specific combinations.

## Key Features

*   **Single Player vs. AI:** Play against a computer opponent.
*   **Dice Rolling:** Players can roll five dice up to three times per turn.
*   **Dice Selection:** Choose which dice to keep and which to re-roll.
*   **Scoring:** Tracks scores based on Yahtzee combinations like "Three of a Kind," "Full House," and "Yahtzee."
*   **AI Opponent:** A computer AI that aims to maximize its score using a combination-selection algorithm.
*   **Text-Based Interface:** Provides a simple command-line user interface.
*   **Colorized Output:** Uses ANSI escape codes for colored text and styled output in the terminal.
*   **Game Instructions:** Offers initial instructions and additional scoring details.
*  **AI Statistics**: Includes statists that show various data on the performance of the AI.
* **Delay Feature**: Includes a delay between each game actions.

## How to Play

1.  **Compilation:**
    Compile the C source code using a C compiler (like GCC):
    ```bash
    gcc your_yahtzee_file.c -o yahtzee
    ```
     (Replace `your_yahtzee_file.c` with the actual name of your file.)

2.  **Execution:**
    Run the compiled program:
    ```bash
    ./yahtzee
    ```

3.  **Gameplay:**
    *   The game will prompt you to enter your name and the AI's name.
    *   Each round, you roll five dice.
    *   The program displays the dice values and available scoring combinations, along with their respective score.
    *   You can choose to keep dice and re-roll the others (up to two more times per round).
    *   The AI will also roll and choose combinations automatically.
    *   Select the combination you want to use based on number printed in the score combinations.
    *   The game will show the final score for each round and proceed to next round.
    *   After 13 rounds, the final scores of both players are displayed and the winner is announced.
    *   You can choose to play again or quit after a game ends.

## Scoring Combinations

Here are the available Yahtzee scoring combinations:

*   **Ones, Twos, Threes, Fours, Fives, Sixes:**  Score the sum of dice showing that number.
*   **Three of a Kind:** Score the sum of all dice if at least three are the same.
*   **Four of a Kind:** Score the sum of all dice if at least four are the same.
*   **Full House:** Score 25 points for three of one number and two of another.
*   **Small Straight:** Score 30 points for four consecutive numbers.
*   **Large Straight:** Score 40 points for five consecutive numbers.
*   **Chance:** Score the sum of all dice.
*   **Yahtzee:** Score 50 points for five of a kind.

## Implementation Details

*   **Programming Language:** C
*   **Random Number Generation:** Uses `srand(time(0))` for pseudo-random dice rolls.
*   **Terminal Styling:** ANSI escape codes for colorizing and formatting output.
*   **Input Handling:** Uses `scanf` and `getchar` for handling user input, with input validation.
*  **Game Logic**: Implemented in logical functions.
*   **Data Structures:** Uses a `struct` to store player information (name, dice, scores, etc.)
* **Algorithms**: the combination picking algothrim is implemented using a loop which calculates the scores of every avilable combinations and picking the max score available.
* **AI**: The AI is designed to obtain higher scores by rerolling and maximizing the score of specific combination by the use of a specific algothrim.

## Code Structure
*   **Header Files:**  Standard libraries such as `<stdio.h>`, `<stdlib.h>`, `<time.h>`, `<string.h>`, `<ctype.h>`, `<unistd.h>`, and `<termios.h>`
*   **Macros for Text Styling:** ANSI escape codes for text color and formatting.
*   **Constants:** `diceFaces`, and `combinationNames` arrays for dice art and name.
*  **Structures:** `players` struct is created for players and AI information.
*   **Functions:** Individual functions for the program logic with specific purposes.
*   **Input functions**: User inputs and format functions are located.
*   **Output Functions:**  Functions that display the dice, scores, and game status, including the winner.
*  **Dice Functions:** A collection of function for generation, dice printing, dicerolls and dice selection.
*  **Score Functions:** A collection of functions for score calculations and updates.
*  **Main Game Function:** The game logic is handled here.
*   **AI Functions:** Functions that handle AI logic are implemented here.
*   **Input validation and Timer functions:**  Functions for input validation and delays between actions.
*   **Statistics Functions**: For the AI, an extra set of functions that generate statistics such as average scores and percentages.

## Additional Notes

*   The program is designed for a standard terminal environment.
*   The code includes input validation to prevent common errors, but further robust error handling could be added.
*   The AI's strategy is deterministic based on the dice. 
*   The game provides detailed instructions at the beginning, you can check it on the game when playing.

## Future Improvements

*   More advanced AI opponent (e.g., using machine learning for better decision-making).
*   Option for multi-player gameplay.
*   Graphical user interface (GUI) version.
*   Additional error handling and input validation.
*   Save/load game feature.
*   More customizations options for the players.

## Author

[Your Name] - [Your Email or GitHub profile]

## Date

[Date of last commit]
