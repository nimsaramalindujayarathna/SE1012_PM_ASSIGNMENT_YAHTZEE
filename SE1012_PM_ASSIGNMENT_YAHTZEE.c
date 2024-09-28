/*
    Author: Jayarathna W.A.N.M IT24103464
    Date: 19.09.2024
    Program: Yahtzee Game

    Description:
    This program simulates a game of Yahtzee, a popular dice game. The game involves rolling 
    five dice up to three times in a turn, aiming to score points by creating specific dice 
    combinations (e.g., three of a kind, four of a kind, full house, etc.).

    Key Features of the Program:
    - Allows single human players to play against the computer.
    - Players can roll dice, choose which dice to keep, and reroll up to three times.
    - The program keeps track of scores based on the combinations rolled.
    - Players can score in various categories such as "Full House", "Three of a Kind", and "Yahtzee".

    Objective:
    The players goal is to maximize the score by strategically rolling the dice and selecting the best combinations.
    The Computer AI specifically designed to maximize its score by using combinations in the optimal way.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_number();
void dice_readings(char *dices);
void printDice(char *dices);

int main() {
    srand(time(0));
    
    char dices[5];
    dice_readings(dices);
    printf("%s\n", dices);
    return 0;
}

//instruction function
void instruct(){
    char charInput;
    printf("This game is played over 13 rounds, and in each round, players can roll the dice up to three times.\nAfter each roll, they can choose to keep or re-roll any number of dice in an attempt to achieve a higher score in one of 13 scoring categories.\n");
    printf("Player can go to next round after the computer player rolled the dices for the current round.\n");
    printf("Do you want more information of the Scoring Dice Combinations. Yes - 'Y'   No - 'N' : ");
    scanf(" %c",&charInput);
    //Input Validation
    while (!(charInput == 'Y' || charInput == 'y' || charInput == 'N' || charInput == 'n')) {
        printf("Invalid char input press either 'Y' or 'N'. Simple letters also works : ");
        scanf(" %c",&charInput);
    }
    if (charInput == 'Y' || charInput == 'y'){
        printf("/n1 to 6:           Score based on the sum of the dice that show the chosen number.\n");
        printf("Three of a Kind:  Score the sum of all dice if at least three of them are the same.\n");
        printf("Four of a Kind:   Score the sum of all dice if at least four of them are the same.\n");
        printf("Full House:       Score 25 points for a combination of three of one number and two of another.\n");
        printf("Small Straight:   Score 30 points for four consecutive numbers.\n");
        printf("Large Straight:   Score 40 points for five consecutive numbers.\n");
        printf("Yahtzee:          Score 50 points for five dice showing the same number.\n");
        printf("Chance:           Score the sum of all dice, regardless of combination.\n");
    }
}


// this function will generate random numbers from 1-6 getting the dice readings
int random_number(){
    return (rand() % 6) + 1;
} 


// this fuction will print the dice readings when the readings array is passed as an parameter
void dice_readings(char *dices) {
    for (int i = 0; i < 5; i++){
        dices[i] = random_number();
    }
}


// this function will generate 5 dice readings and store them in an array and the array name will be passed as an parameter
void printDice(char *dices){
    for (int i = 0; i < 5; i++){
        printf("%d ",dices[i]);
    }
    printf("\n");
}
