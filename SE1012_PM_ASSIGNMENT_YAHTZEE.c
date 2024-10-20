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
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// Normal Text Colors
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Text Styles 
#define BOLD           "\033[1m"
#define DIM            "\033[2m"
#define ITALIC         "\033[3m"
#define UNDERLINED     "\033[4m"
#define BLINKING       "\033[5m"
#define HIGH_SCORE_TEXT "\033[1m\033[30m"  
#define HIGH_SCORE_BG "\033[46m" 

// Reset Code
#define RESET "\033[0m"

const char *combinationNames[13] = {
    "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes",
    "Three of a Kind", "Four of a Kind", "Full House",
    "Small Straight", "Large Straight", "Chance", "YAHTZEE"
};

typedef struct {
    char name[25];
    char dice[5];
    int scoredScore[13];
    int uScore;
    int lScore;
    int total;
    int combinations[13];
    int index;
}players;

////FUNCTION PROTOTYPE
int random_number();
int chance(char * dices);
int yahtzee(char *dices);
int fullHouse(char *dices);
int bonus(int numbersScore);
int fourOfaKind(char *dices);
int threeOfaKind(char *dices);
int largeStraight(char *dices);
int smallStraight(char *dices);
void timer(int time);
void next();
void instruct();
void important();
void clearInputs();
void AIName(char *name);
void editName(char *name);
void playerName(char *name);
void diceReadings(char *dices);
void AINumbers (char *dices, int index, int roll);
void AIIndex(char *dices, int *comArray, int *AIIndex);
void AISingleRollAgain(char *dices, int index, int roll);
void AIscoreCal(char *dices, int combinationNum, int *score);
void diceRollWithSingleIndex(char*dices, int index, int roll);
void printDice(char *dices, int lineBreak, int color, int time);
void winner(int userFinal, int AIFinal, char *playerName, char *AIName);
void diceRollWithDoubleIndex(char*dices, int index1, int index2, int roll);
void scoreDisplay(char *name, int nScore, int oScore, int *total, int color);
void printScoresForUser(char *dices, int *combinationsArray, const char *com[]);
void scoreForCombination(char *dices, int *combination, int *score, char *name);
void AIscoreForCombination(char *dices, int combinationNum, int *score, char *name);
void userIndex(char *dices, const char *com[], int *combinationArray,int *AIcombinationArray, int *combinationIndexNumber, char *name, char *AIname, int *Score, int*AIScore, int check, int n, int o, int AIn, int AIo);
void runningFun(char *dices, const char *com[], int *combinationArray,int *AIcombinationArray, int *combinationIndexNumberPointer, int *nScore, int *oScore, char *AIdices, int *AInScore, int *AIoScore, char *playerName, char *AIName, int *Score, int *AIScore);


////////FUNCTIONS DECLRATIONS

//inputs
void editName(char *name) {
    //this function gets the names of the players as parameter and format the name by removing spaces on the name 
    //on each side and capitalize the first character of the name.
    int idx = 0;
    int start = 0;
    int end = strlen(name) - 1;
    char out[26];
    name[strcspn(name, "\n")] = '\0'; // remove the nweline part of the string and replace it with \0
    while (isspace(name[start])) { // remove the spaces in the beggining
        start++;
    }
    while (end >= start && isspace(name[end])) { //remove space at theend
        end--;
    }
    for (int i = start; i <= end; i++) {
        out[idx++] = name[i];
    }
    out[idx] = '\0';
    out[0] = toupper(out[0]);
    strncpy(name, out,idx + 1);
}

void playerName(char *name) {
    //this function passes the players name that is inputted by the user and passes it to the 
    //pointer addres of the sturcture as the parameter and also format the name before passing it.
    printf(RESET CYAN"\nEnter the player's name (character limit 20): ");
    fgets(name, 24, stdin);
    editName(name);
}

void AIName(char *name) {
    //this function passes the AI name that is inputted by the user and passes it to the 
    //pointer addres of the sturcture as the parameter and also format the name before passing it.
    printf(RESET MAGENTA"Enter the AI's name (character limit 20): ");
    fgets(name, 24, stdin);
    editName(name);
    printf(RESET);
}


//outputs
int bonus(int numbersScore){
    //this functions argumnet is the final score adn decides the bonus score and retunrs it 
    //occording to the upper combinations score
    return (numbersScore > 62)? 35:0;
}

void scoreDisplay(char *name, int nScore, int oScore, int *total, int color) {
    //this function arguments are the players name and there respective scores of upper and lower combinations
    // and the respective total of the player. display how the score has been made for the player.
    int tot;
    if (color == 0){
        printf(BOLD CYAN"\n%15s's Score.\n"RESET, name);
    } else if (color == 1) {
        printf(BOLD MAGENTA"\n%15s's Score.\n"RESET, name);
    }
    printf("Upper Combination Score : %3d\n", nScore);
    printf("Lower Combination Score : %3d\n", oScore);
    printf("Bonus Score             : %3d\n", bonus(nScore));
    tot = nScore + oScore + bonus(nScore);
    if (color == 0){
        printf(CYAN BOLD"%15s's Final Score : %3d\n"RESET,name, tot);
    } else if (color == 1) {
        printf(BOLD MAGENTA"%15s's Final Score : %3d\n"RESET,name, tot);
    }
    *total = tot;
}

void winner(int userFinal, int AIFinal, char *playerName, char *AIName) {
    //this function 's arguments are the final score and the names of the two players adn decides who won 
    //and prints the result
    printf("\n");
    if(userFinal < AIFinal){
        printf(BOLD MAGENTA"You tried your best but %s is just better."RESET, AIName);
    } else if(userFinal > AIFinal) {
        printf(BOLD CYAN"Congratulations, %s have won the game"RESET, playerName);
    } else if(userFinal == AIFinal) {
        printf(BOLD ITALIC BLUE"IT'S a DRAW!!!"RESET);
    }
    printf("\n\n");
}

void instruct(){
    //gives the player the necessary instruction to play.
    char charInput;
    printf (DIM
        "\n\nThis game is played over 13 rounds, and in each round, players can roll the dice up to three times.\
        \nAfter each roll, they can choose to keep or re-roll any number of dice readings.\
        \nChoose the best combination out of the combinations available.\
        \nPlyer has to achieve a higher score than the computer player in order to win.\
        \nPlayer can go to next round after the computer player rolled the dices for the current round.\
        \n\nDo you want more information of the Scoring Dice Combinations. Yes - 'Y'   No - 'N' : " 
    );
    //Input Validation
    while(1) {
        if (scanf(" %c", &charInput) != 1) {
            clearInputs();
            printf(RESET YELLOW BLINKING"\nInvalid Input.Please enter only single character. ");
            continue;
        }
        if (charInput == 'Y' || charInput == 'y' || charInput == 'N' || charInput == 'n') {
            clearInputs();
            break;
        } else {
            printf(RESET RED BLINKING"Invalid char input press either 'Y' or 'N'. Simple letters also works : ");
            clearInputs();
        }
    }
    if (charInput == 'Y' || charInput == 'y'){
        printf(RESET DIM"\n1 to 6:           Score based on the sum of the dice that show the chosen number.\n");
        printf("Three of a Kind:  Score the sum of all dice if at least three of them are the same.\n");
        printf("Four of a Kind:   Score the sum of all dice if at least four of them are the same.\n");
        printf("Full House:       Score 25 points for a combination of three of one number and two of another.\n");
        printf("Small Straight:   Score 30 points for four consecutive numbers.\n");
        printf("Large Straight:   Score 40 points for five consecutive numbers.\n");
        printf("Yahtzee:          Score 50 points for five dice showing the same number.\n");
        printf("Chance:           Score the sum of all dice, regardless of combination.\n\n" RESET);
    }
}

void important() {
    //gives the player some important information to keep on mind when playing
    int check = 0;
    while (check != '1') {
        printf(RESET ITALIC BOLD RED
            "\n----------------------------- IMPORTANT NOTICE FOR THE PLAYERS -----------------------------\
            \nWhen processing an input from here on, only the first character is considered.\
            \nOnly input you can input two characters is the Conditions input.\
            \nSo keep that in mind when playing.\
            \nPress '1' to play : " RESET
            );
        check = getchar();
        clearInputs();
    }
    //clearInputs();
}

void next(){
    //this function is specifically designed to take a user input to proceed to the next round.
    // main target to get user input is to get the user's attention when displaying there scores for each round
    printf(DIM"Proceed to the next round. Press anykey and enter."RESET);
    getchar();
    clearInputs();
    printf("\n");
}


//dice readings
int random_number(){
    // this function will generate random numbers from 1-6 for the dice readings
    return (rand() % 6) + 1;
} 

void diceReadings(char *dices) {
    // this fuction will store 5 randome numbers as dice readings when the each players dice array is passed as an argument
    for (int i = 0; i < 5; i++){
        dices[i] = random_number();
    }
}

void printDice(char *dices, int lineBreak, int color, int time){
    //this function will print the dice readings of the string that passes as the dices pointer. 
    //if the linebreak value is one when calling the function prints a linebreak when printing the dice readings
    //if the linebreak value is zero when calling the function, just print the dice readings
    if (lineBreak == 1){
        printf("\n");
    }
    printf(ITALIC BOLD"Dice Readings are : " RESET);
    printf("[");
    if (color == 0) {
        for (int i = 0; i < 5; i++){
            if (time == 1){
                timer(700);
            }
            printf(BOLD CYAN"%d" RESET,dices[i]);
            if ((time == 1) && (i == 4)){
                timer(700);
            }
            if(i < 4){
                printf(" ");
            }
        }
    } else if (color == 1) {
        for (int i = 0; i < 5; i++){
            if (time == 1){
                timer(700);
            }
            printf(BOLD MAGENTA"%d" RESET,dices[i]);
            if ((time == 1) && (i == 4)){
                timer(700);
            }
            if(i < 4){
                printf(" ");
            }
        }
    }
    printf("]\n");
}

void diceRoll(char *dices, int *combinationsArray, const char *com[]) {
    // this function will roll the dice 3 times and get the readings according to the user's preference and the array which use to store the readings are passed as argument(pointer)
    char tempDices[5]; //tempary array to store temp dices
    int indexes; //indexs to keep
    int NoOfIndexes; // no of the indexes to keep
    char inputChar; 
    int i = 0;
    timer(1000);
    printf(ITALIC BOLD"\n\tRoll NO (%d) >>>> " RESET ,i+1);// this selection print the roll no
    timer(500);
    diceReadings(dices); //Inital dice roll
    printDice(dices, 0, 0, 1); //Inital deice reads displayed
    printScoresForUser(dices, combinationsArray, com);
    for (i = 0; i < 2; i++) {
        int indexCheckArray[] = {0, 0, 0, 0, 0};
        timer(600);
        printf("If you want to roll the dices again     ");
        printf(RESET BOLD ITALIC "Press ---- 'Y'\n"RESET);
        timer(600);
        printf("If you want to keep this dice readings  ");
        printf(RESET BOLD ITALIC "Press ---- 'N'\n"RESET);
        timer(600);
        printf("Enter your decision : ");
        scanf(" %c",&inputChar);
        // input validation ---- inputChar
        while(!(inputChar == 'Y' || inputChar == 'y' || inputChar == 'N' || inputChar == 'n')){
            clearInputs();
            printf(BOLD RED BLINKING"Invalid input! Please press 'Y' to roll again or 'N' to stop rolling.\n"RESET);
            printf("Enter your decision : ");
            scanf(" %c",&inputChar);
        }
        clearInputs();
        if (inputChar == 'Y' || inputChar == 'y') {
            for (int j = 0; j < 5; j++ ) {
                tempDices[j] = dices[j]; //store the main array data to temp array to roll the dices again, while the values in the temp arrary are used to do the execution
            }
            diceReadings(dices); // next dice rolls. actually the programm roll the dice and store it in a temp array before asking the user what to do with the previous dice readings.
            timer(500);
            printf("Enter how many dice readings you want to keep before the next roll : ");
            //input validation ---- NoofIndexes
            while(1) {
                if (scanf("%d", &NoOfIndexes) != 1) {
                    printf(ITALIC YELLOW BLINKING"Invalid Input type. Please enter again. [0, 1, 2, 3, 4] : "RESET);
                    clearInputs();   
                    continue;
                }
                if ((NoOfIndexes < 0) || (NoOfIndexes > 4)) {
                    printf(BOLD RED BLINKING"Invalid number of indexes. Please enter again. [0, 1, 2, 3, 4] : "RESET);
                    clearInputs();   
                    continue;
                }
                clearInputs();
                break;
            }
            if (NoOfIndexes == 1) {
                timer(400);
                printf("Enter the index number of the dice reading you wanted keep. (1 to 5)\n");
            } else if (NoOfIndexes > 1){
                timer(400);
                printf("Enter the index numbers of the dice readings you wanted keep. (1 to 5)\n");
            }
            for (int ii = 1; ii < NoOfIndexes + 1; ii++){
                timer(400);
                printf("Enter the index number %d (1 to 5): ", ii );
                while(1) {
                    if (scanf("%d", &indexes) != 1) {
                        printf(ITALIC YELLOW BLINKING"Invalid Input type. Please enter again. (1 to 5) : "RESET);
                        clearInputs();
                        continue;
                    }
                    if ((indexes < 1) || (indexes > 5)) {
                        printf(BOLD RED BLINKING"Incorrect index enterd. Please enter again. (1 to 5) : "RESET);
                        clearInputs();
                        continue;
                    }
                    if (indexCheckArray[indexes - 1] == 1) {
                        printf(DIM GREEN"You entered the same index again. Please enter a different index. (1 to 5) : "RESET);
                        clearInputs();
                        continue;
                    }
                    break;
                }
                indexCheckArray[indexes -1] = 1;
                dices[indexes - 1] = tempDices[indexes - 1 ]; // the main array store the next roll data and occording to the indexes the values decided keep are assigned into the newly rolled main array
            }
            timer(1000); 
            printf(BOLD ITALIC"\n\n\tRoll NO (%d) >>>> "RESET,i+2);
            timer(500); 
            if (NoOfIndexes != 0) {
                clearInputs();
            }
            printDice(dices, 0, 0, 1); // print the new dices rolls
            printScoresForUser(dices, combinationsArray, com);
        } else if (inputChar == 'N' || inputChar == 'n') {
            break; // if the user do not want to roll again escape the function
        } 
    }
    //clearInputs();
    timer(600);
    printf(BOLD ITALIC"\n\tFinal " RESET);
    printDice(dices , 0, 0, 0); // after 3 dice rools or users's prefered dice rolls print  the dices
}


/*below functions are used to calculate the score for each lower combination when the dice readings are passed as an argument.
the score is returned when calling the function*/
int chance(char * dices){
    int sum = 0;
    for (int i = 0; i < 5;i++){
        sum = sum + dices[i];
    }
    return sum;
}

int yahtzee(char *dices){
    int sum = 50;
    int temp = dices[0];
    for (int i = 0; i < 5; i++){
        if(!(temp == dices[i])){
            sum = 0;
            break;
        }
    }
    return sum;
}

int largeStraight(char *dices) {
    int array[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        array[dices[i] - 1]++ ;
    }
    if((array[0] == 1 && array[1] == 1 && array[2] == 1 && array[3] == 1 && array[4] == 1) ||
       (array[1] == 1 && array[2] == 1 && array[3] == 1 && array[4] == 1 && array[5] == 1)) {
        return 40;
    } else {
        return 0;
    }
}

int smallStraight(char *dices) {
    int array[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        array[dices[i] - 1]++ ;
    }
    if((array[0] >= 1 && array[1] >= 1 && array[2] >= 1 && array[3] >= 1) ||
       (array[1] >= 1 && array[2] >= 1 && array[3] >= 1 && array[4] >= 1) ||
       (array[2] >= 1 && array[3] >= 1 && array[4] >= 1 && array[5] >= 1)) {
        return 30;
    } else {
        return 0;
    }
}

int fullHouse(char *dices){
    int sum = 0;
    int array1[] = {0, 0, 0, 0, 0, 0};
    int kindOfThreeCheck = 0;
    int kindOfTwoCheck = 0;
    for (int i = 0; i < 5; i++) {
        array1[dices[i] - 1]++ ;
    }
    for (int j = 0; j < 6; j++) {
        if (array1[j] == 3){
            kindOfThreeCheck = 1;
        }
    }
    for (int k = 0; k < 6; k++){
        if (array1[k] == 2){
            kindOfTwoCheck = 1;
        } 
    }
    if((kindOfThreeCheck == 1) && (kindOfTwoCheck == 1)) {
        sum = 25;
    } else {
        sum = 0;
    }
    return sum;
}

int fourOfaKind(char *dices){
    int sum = 0;
    int array1[] = {0, 0, 0, 0, 0, 0};
    for (int ii = 0; ii < 5; ii++) {
        array1[dices[ii] - 1]++ ;
    }
    for (int j = 0; j < 6; j++) {
        if (array1[j] >= 4){
            for (int i = 0; i < 5; i++){
                sum += dices[i];
            }
            return sum;
        }
    }
    return 0;
}

int threeOfaKind(char *dices){
    int sum = 0;
    int array1[] = {0, 0, 0, 0, 0, 0};
    for (int ii = 0; ii < 5; ii++) {
        array1[dices[ii] - 1]++ ;
    }
    for (int j = 0; j < 6; j++) {
        if (array1[j] >= 3){
            for (int i = 0; i < 5; i++){
                sum += dices[i];
            }
            return sum;
        }
    }
    return 0;
}


//main function that are used to play the game for the user's sside
void userIndex(char *dices, const char *com[], int *combinationArray,int *AIcombinationArray, int *combinationIndexNumber, char *name, char *AIname, int *Score, int*AIScore, int check, int n, int o, int AIn, int AIo){
    ////this function is used to get the user's prefered combination for each dice rounds
    // arguments users dice readings, combination names string, combination array is used to pass and check the already selected combinations,
    // index number is used to calculate the score.
    int index;
    char spaces[] = {" "};
    if (check == 0) {
        printf("\nCombinations Available to Choose.\n\n");
        timer(750);
    } else if (check == 1) {
        printf("\nAll the Combinations were used.\n\n");
        timer(750);
    }
    // this prints the currently available combinations for user to choose from.
    printf("%20s's Combinations\t  %20s's Combinations\n",name, AIname);
    for (int i = 0; i < 13; i++) { 
        if (i == 5) {
            if (combinationArray[i] == 0){
                printf("\t\t%2d. %-16s %3d ",(i+1),com[i],Score[i]);
                printf(BOLD "%3d"RESET, n);
            } else if (combinationArray[i] == 1){
                printf(DIM "\t\t%2d. %-16s %3d " RESET,(i+1),com[i], Score[i]);
                printf(BOLD "%3d"RESET, n);
            }
            if (AIcombinationArray[i] == 0){
                printf("\t |\t%2d. %-16s %3d ", (i+1), com[i], AIScore[i]);
                printf(BOLD "%3d\n" RESET, AIn);
            } else if (AIcombinationArray[i] ==1) {
                printf("\t |");
                printf(DIM"\t%2d. %-16s %3d " RESET,(i+1),com[i], AIScore[i]);
                printf(BOLD "%3d\n" RESET, AIn);
            }
        } else if (i == 12) {
            if (combinationArray[i] == 0){
                printf("\t\t%2d. %-16s %3d ",(i+1),com[i],Score[i]);
                printf(BOLD "%3d" RESET, o);
            } else if (combinationArray[i] == 1){
                printf(DIM "\t\t%2d. %-16s %3d " RESET,(i+1),com[i], Score[i]);
                printf(BOLD "%3d" RESET, o);
            }
            if (AIcombinationArray[i] == 0){
                printf("\t |\t%2d. %-16s %3d ", (i+1), com[i], AIScore[i]);
                printf(BOLD "%3d\n" RESET, AIo);
            } else if (AIcombinationArray[i] ==1) {
                printf("\t |");
                printf(DIM"\t%2d. %-16s %3d " RESET,(i+1),com[i], AIScore[i]);
                printf(BOLD "%3d\n" RESET, AIo);
            }
        }else {
            if (combinationArray[i] == 0){
                printf("\t\t%2d. %-16s %3d",(i+1),com[i],Score[i]);
            } else if (combinationArray[i] == 1){
                printf(DIM "\t\t%2d. %-16s %3d " RESET,(i+1),com[i], Score[i]);
            }
            if (AIcombinationArray[i] == 0){
                printf("\t |\t%2d. %-16s %3d\n", (i+1), com[i], AIScore[i]);
            } else if (AIcombinationArray[i] ==1) {
                printf("\t |");
                printf(DIM"\t%2d. %-16s %3d \n" RESET,(i+1),com[i], AIScore[i]);
                //printf("\t\t%21s %5d\n", spaces,AIScore[i]);
            }
        } 
    }
    timer(1200);
    printf(BOLD "\t\t    Current Total Score: %3d" RESET , o + n);
    printf(BOLD "\t\t    Current Total Score: %3d" RESET , AIo + AIn);
    printf("\n\n");
    if (check == 1) {
        return;
    }
    diceRoll(dices, combinationArray, com);
    //input validation for indexI variable
    while (1) {
        printf(BOLD"\n\tChoose an available combination no (1 to 13): "RESET);
        if (scanf("%d", &index) != 1) {  //check if the input is integer
            printf(ITALIC YELLOW BLINKING"Invalid input type! Please enter a number between 1 and 13.\n"RESET);
            clearInputs();  // clear additional inputs
            continue;
        }
        if (index < 1 || index > 13) { //for out of ranges inouts
            printf(BOLD RED BLINKING"Invalid input value. Please enter a number between 1 and 13.\n"RESET);
            clearInputs();
            continue;
        } 
        if (combinationArray[index - 1] == 1) { // for prevoiously inutted value check
            printf(DIM GREEN"This combination has already been chosen! Please pick another.\n"RESET);
            clearInputs();
            continue;
        } 
        break;  // if the input is valid loop break
    }
    combinationArray[index - 1] = 1;
    *combinationIndexNumber = index;
    clearInputs();
}

void scoreForCombination(char *dices, int *combinationNum, int *score, char *name){
    //this function will produce the score when the combination type is inputted
    //arguments respcetives players dice readings, combinations seleceted by the user or AI, pointer to retuen the score to the struct
    //respective playesr name
    int tempscore = 0;
    int combination = *combinationNum;
    if (combination < 7){
        for (int i = 0; i < 5; i++) {
            if (dices[i] == combination) {
                tempscore = tempscore + dices[i];
            }
        }
    }
    else if(combination == 7) {
        tempscore = threeOfaKind(dices);
    } else if(combination == 8) {
        tempscore = fourOfaKind(dices);
    } else if(combination == 9) {
        tempscore = fullHouse(dices);
    } else if(combination == 10) {
        tempscore = smallStraight(dices);
    } else if(combination == 11) {
        tempscore = largeStraight(dices);
    } else if(combination == 12) {
        tempscore = chance(dices);
    } else if(combination == 13) {
        tempscore = yahtzee(dices);
    }
    *score = tempscore;
    printf("\t%s's score for this round = ",name);
    timer(500);
    printf(CYAN BOLD "%d\n"RESET, tempscore);
    timer(500);
}

void AIscoreForCombination(char *dices, int combinationNum, int *score, char *name){
    /// this function will produce the score when the combination type is inputted - for the AI
    int tempscore = 0;
    if (combinationNum < 7){
        for (int i = 0; i < 5; i++) {
            if (dices[i] == combinationNum) {
                tempscore = tempscore + dices[i];
            }
        }
    }
    else if(combinationNum == 7) {
        tempscore = threeOfaKind(dices);
    } else if(combinationNum == 8) {
        tempscore = fourOfaKind(dices);
    } else if(combinationNum == 9) {
        tempscore = fullHouse(dices);
    } else if(combinationNum == 10) {
        tempscore = smallStraight(dices);
    } else if(combinationNum == 11) {
        tempscore = largeStraight(dices);
    } else if(combinationNum == 12) {
        tempscore = chance(dices);
    } else if(combinationNum == 13) {
        tempscore = yahtzee(dices);
    }
    *score = tempscore;
    printf("\t%s's score for this round = ",name);
    timer(500);
    printf(MAGENTA BOLD "%d\n\n"RESET, tempscore);
    timer(500);
}

void AIscoreCal(char *dices, int combinationNum, int *score){
    /// this function will produce the score when the combination type is inputted - for the AI
    int tempscore = 0;
    if (combinationNum < 7){
        for (int i = 0; i < 5; i++) {
            if (dices[i] == combinationNum) {
                tempscore = tempscore + dices[i];
            }
        }
    }
    else if(combinationNum == 7) {
        tempscore = threeOfaKind(dices);
    } else if(combinationNum == 8) {
        tempscore = fourOfaKind(dices);
    } else if(combinationNum == 9) {
        tempscore = fullHouse(dices);
    } else if(combinationNum == 10) {
        tempscore = smallStraight(dices);
    } else if(combinationNum == 11) {
        tempscore = largeStraight(dices);
    } else if(combinationNum == 12) {
        tempscore = chance(dices);
    } else if(combinationNum == 13) {
        tempscore = yahtzee(dices);
    }
    *score = tempscore;
}

void runningFun(char *dices, const char *com[], int *combinationArray,int *AIcombinationArray, int *combinationIndexNumberPointer, int *nScore, int *oScore, char *AIdices, int *AInScore, int *AIoScore, char *playerName, char *AIName, int *Score, int*AIScore){
    //this is the second top priority functions of the game, this function will loop 13 rounds of the game.
    //there are many arguments to this function, all the other functions are called inside this function.
    //such as every deails of the player and the AI,combinations names, dices readings, userprefferd combination no
    int tempscore; // score for the respective condition
    int AItempscore; // score for the respective AI combination
    int sum1 = 0;
    int sum2 = 0;
    int AIsum1 = 0;
    int AIsum2 = 0;
    int AIIndexNum;
    int playerIndex;
    for (int i = 0; i < 13; i++) {
        Score[i] = 0;
        AIScore[i] = 0;
        combinationArray[i] = 0;
        AIcombinationArray[i] = 0;
    }
    for (int i = 0; i < 13; i++) {
        printf(BOLD ITALIC"\n\n\n****************************************  Round No %d  ****************************************\n"RESET,i+1);    
        userIndex(dices,com ,combinationArray, AIcombinationArray, combinationIndexNumberPointer, playerName,AIName, Score, AIScore, 0, sum1, sum2, AIsum1, AIsum2);
        printf(DIM"---------------------------------------------------------------------------------------------\n"RESET);
        diceReadings(AIdices);
        printf("\n\t");
        printf(BOLD UNDERLINED"%s's dice readings\n"RESET,AIName);
        timer(1000);
        printf(BOLD ITALIC"\tRoll NO (1) - "RESET);
        timer(500);
        printDice(AIdices, 0, 1, 1);
        AIIndex(AIdices, AIcombinationArray, &AIIndexNum );
        printf(DIM"\n---------------------------------------------------------------------------------------------"RESET);
        printf(BOLD ITALIC"\n\n\t%s's Final "RESET,playerName);
        timer(500);
        printDice(dices, 0, 0, 0);
        printf("\tCombination Type : " );
        timer(350);
        printf(BOLD CYAN"%-16s\t"RESET ,com[*combinationIndexNumberPointer - 1]);
        timer(500);
        scoreForCombination(dices, combinationIndexNumberPointer, &tempscore, playerName);
        timer(1000);
        if (*combinationIndexNumberPointer < 7) {
            sum1 = sum1 + tempscore;
        } else {
            sum2 = sum2 + tempscore;
        }
        playerIndex = *combinationIndexNumberPointer;
        Score[playerIndex - 1] = tempscore;
        printf(BOLD ITALIC"\n\t%s's Final "RESET,AIName);
        timer(500);
        printDice(AIdices, 0, 1, 0);
        printf("\tCombination Type : ");
        timer(350);
        printf(BOLD MAGENTA"%-16s\t"RESET, com[AIIndexNum]);
        timer(500);
        AIscoreForCombination(AIdices, AIIndexNum + 1, &AItempscore, AIName);
        timer(1000);
        if (AIIndexNum+1 < 7) {
            AIsum1 = AIsum1 + AItempscore;
        } else {
            AIsum2 = AIsum2 + AItempscore;
        }               
        AIScore[AIIndexNum] = AItempscore;
        if (i < 12) {
            next();
        } 
    }
    *nScore = sum1;
    *oScore = sum2;
    *AInScore = AIsum1;
    *AIoScore = AIsum2;
    userIndex(dices,com ,combinationArray, AIcombinationArray, combinationIndexNumberPointer, playerName,AIName, Score, AIScore, 1, sum1, sum2, AIsum1, AIsum2);
}

void printScoresForUser(char *dices, int *combinationsArray, const char *com[]) {
    int sscores[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int maxScore = 0;
    for (int i = 0; i < 13; i++) {
            AIscoreCal(dices, i + 1, &sscores[i]);
    }
    printf("\n  ");
    printf(UNDERLINED"Score for every Combination availabel for the current dice Readings"RESET);
    printf("\n\n");
    for (int i = 0; i < 13; i++) {
        if ((combinationsArray[i] == 0) && (maxScore < sscores[i])){
            maxScore = sscores[i];
        }
    }
    for (int i = 0; i < 13; i++) {
        if (combinationsArray[i] == 0){
            if((sscores[i] == maxScore)  && (!(maxScore == 0))) {
                timer(250);
                printf("\t\t  ");
                printf(HIGH_SCORE_BG HIGH_SCORE_TEXT"%2d. %-16s %2d"RESET, i+1, com[i], sscores[i]);
                printf("\n");
            } else {
                timer(250);
                printf("\t\t  %2d. %-16s %2d\n", i+1, com[i], sscores[i]);
            }
        }
    }
    printf("\n");
}


//Ai functions
void AIIndex(char *dices, int *comArray, int *AIIndex) {
    // this is the main function that implements the AI.
    // parameter are the AI's dice readings, combination check array to check which combinations were selected, respective index no for the selected combination is pointed to a variable where it is called.
    // this function will choose the best combination out of the available combinations by comparing the scores for each combination
    // also inside this function fi there are 3same dice reading they rolled agan in order to obtain a four of akind or a yahtzee, vi versa for the 4 same dices redaings.
    int scores[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int index = 99;
    int scorecheck = 0;
    int sortNumber = 0;
    for (int l = 0; l < 3; l++) {
        int sortedArray[] = {0, 0, 0, 0, 0, 0}; 
        for (int i = 0; i < 5; i++) {
            sortedArray[dices[i] - 1]++ ;
        }
        for (int i = 0; i < 6; i++) {
            if (sortedArray[i] == 4 || sortedArray[i] == 3) {
                sortNumber = sortedArray[i];
            }
        }
        for (int i = 0; i < 13; i++) {
            AIscoreCal(dices, i + 1, &scores[i]);
        }
        int temp = 0;
        for (int i = 0; i < 13; i++) {
            if (comArray[i] == 0) {
                if (i == 11) { // skipping chances combination until 11+ round
                    continue;
                } 
                if (temp < scores[i]) {
                    temp = scores[i];
                    index = i;
                    if (i == 12) { //prioritising the yahtzee and full house combinations.
                        goto end1;
                    }
                    if (i == 8) {
                        goto end1;
                    }
                } else if (temp == scores[i] && (i == 6 || i == 7)) {
                    index = i;
                }
            }
        }
        if (index > 7 && index != 99 && index != 12) {
            goto end1; // skip if the combinations is yahtzee or  
        }
        if (l < 2){
            if(comArray[12] == 0 || comArray[6] == 0 || comArray[7] == 0) {
                if (sortNumber == 3) {
                    AISingleRollAgain(dices, 6, l);
                    continue;
                }
                if (sortNumber == 4) {
                    AISingleRollAgain(dices, 7, l);
                    continue;
                }
            }
            if (index < 6) {
                AINumbers(dices, index, l);
                continue;
            }
        }
        if (index == 99) {
            for (int i = 0; i < 13; i++) {
                if (comArray[i] == 0) {
                    index = i;
                    switch (l) {
                        case 0:
                            diceReadings(dices);
                            timer(1000);
                            printf(BOLD ITALIC"\tRoll NO (2) - "RESET);
                            timer(500);
                            printDice(dices,0, 1, 1);
                            break;
                        case 1:
                            diceReadings(dices);
                            timer(1000);
                            printf(BOLD ITALIC"\tRoll NO (3) - "RESET);
                            timer(500);
                            printDice(dices,0, 1, 1);
                            break;
                        default:
                            break;
                    }
                    break;;
                }
            }
        }
    }
    end1:
    comArray[index] = 1;
    *AIIndex = index; 
}

void AISingleRollAgain(char *dices, int index, int roll) {
    // this function is designed to roll the Ai dice reaings, if only one dice is needed to be rolled.
    // parameteres are the AI dices index which the dice reaings should roll, and the roll no to display
    // if the index is 6 it will run the singleindex function which can only roll 1 dice.
    // if the inedx is 7 it will run the double index function which can roll upto 2 dice readings.
    int singleNumber, indexNo, index1, index2;
    int sortedArray[] = {0, 0, 0, 0, 0, 0}; 
    for (int i = 0; i < 5; i++) {
        sortedArray[dices[i] - 1]++ ;
    }
    if(index == 7) { //checking whether the dices are needed to change 1 or 2 readings.
        for (int i = 0; i < 5; i++) {
            if (sortedArray[i] == 1) {
                singleNumber = i + 1;
                break;
            }
        }
        for (int i = 0; i < 5; i++) {
            if (dices[i] == singleNumber) {
                indexNo = i;
                break;
            }
        }
        diceRollWithSingleIndex(dices, indexNo, roll);
    }
    if (index == 6) {
        int num1, num2;
        int temp1 = 0;
        int temp2 = 0;
        for (int i = 0; i < 6; i++) {
            if (sortedArray[i] == 1 && temp1 == 0) {
                num1 = i + 1;
                temp1 = 1;
            } else if (sortedArray[i] == 1 && temp1 ==1) {
                num2 = i + 1;
                break;
            }
        }
        for (int i = 0; i < 5; i++) {
            if ((dices[i] == num1 && temp2 == 0) || (dices[i] == num2 && temp2 == 0)) {
                index1 = i;
                temp2 = 1;
            } else if ((dices[i] == num1 && temp2 == 1) || (dices[i] == num2 && temp2 == 1) ) {
                index2 = i;
                break;
            }
        }
        diceRollWithDoubleIndex(dices, index1, index2, roll);
    }
}

void diceRollWithSingleIndex(char*dices, int index, int roll) {
    // this function is designed to roll the Ai dice reaings, if only single dice is needed to be rolled.
    // parameteres are the AI dices indexes which the dice readings should roll, and the roll no to display
    int tempArray[] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        tempArray[i] =  dices[i];
    }
    diceReadings(dices);
    for (int i = 0; i < 5; i++) {
        if (i == index){
            continue;
        } 
        dices[i] =  tempArray[i];
    }
    switch (roll) {
        case 0:
            timer(1000);
            printf(BOLD ITALIC"\tRoll NO (2) - "RESET);
            timer(500);
            printDice(dices, 0, 1, 1);
            break;
        case 1:
            timer(1000);
            printf(BOLD ITALIC"\tRoll NO (3) - "RESET);
            timer(500);
            printDice(dices, 0, 1, 1);
            break;
        default:
            break;
    }
}

void diceRollWithDoubleIndex(char*dices, int index1, int index2, int roll) {
    // this function is designed to roll the Ai dice reaings, if only two dices are needed to be rolled.
    // parameteres are the AI dices indexes which the dice readings should roll, and the roll no to display
    int tempArray[] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        tempArray[i] =  dices[i];
    }
    diceReadings(dices);
    for (int i = 0; i < 5; i++) {
        if (i == index1 || i == index2){
            continue;
        } 
        dices[i] =  tempArray[i];
    }
    switch (roll) {
        case 0:
            timer(1000);
            printf(BOLD ITALIC"\tRoll NO (2) - "RESET);
            timer(500);
            printDice(dices, 0, 1, 1);
            break;
        case 1:
            timer(1000);
            printf(BOLD ITALIC"\tRoll NO (3) - "RESET);
            timer(500);
            printDice(dices, 0, 1, 1);
            break;
        default:
            break;
    }
}

void AINumbers (char *dices, int index, int roll) {
    // this function is designed to roll the dices again if the best combination is choose as a upper combination.
    // this function will try to rolll the dices again to get more of the same number which is choosn for the combination.
    int tempArray[] = {0, 0, 0, 0, 0};
    int diceNumber = index + 1;
    for (int i = 0; i < 5; i++) {
        if (dices[i] == diceNumber) {
            tempArray[i] = dices[i];
        }
    }
    diceReadings(dices);
    for (int i = 0; i < 5; i++) {
        if (tempArray[i] != 0) {
            dices[i] = tempArray[i];
        }
    }
    switch (roll) {
        case 0:
            timer(1000);
            printf(BOLD ITALIC"\tRoll NO (2) - "RESET);
            timer(500);
            printDice(dices, 0, 1, 1);
            break;
        case 1:
            timer(1000);
            printf(BOLD ITALIC"\tRoll NO (3) - "RESET);
            timer(500);
            printDice(dices, 0, 1, 1);
            break;
        default:
            break;
    }
}


//other mini functions used for the input validation of the game and delays
void clearInputs() {
    // this function is used to get the inputs in the correct data type.
    int input;
    while ((input = getchar()) != '\n' && input != EOF);  // remove invalid inputs and clear other inputs EOF - end of file
}

void timer(int time) {
    fflush(stdout);
    usleep(time * 1000);
}



int main() {
    srand(time(0));// only call once. this will generate random numbers compared to the time in seconds. this will remove the squential random number ger=neration.

    //defining the structures
    players user;
    players AI;

    //instructions to play 
    instruct();

    // input the names of the players
    playerName(user.name);
    AIName(AI.name);

    //important information how the games should be played
    important();

    //running Function
    runningFun(user.dice, combinationNames, user.combinations, AI.combinations, &user.index, &user.uScore, &user.lScore, AI.dice, &AI.uScore, &AI.lScore, user.name, AI.name, user.scoredScore, AI.scoredScore);
    
    //display final Score
    scoreDisplay(user.name, user.uScore, user.lScore, &user.total, 0);
    scoreDisplay(AI.name, AI.uScore, AI.lScore, &AI.total, 1);

    //choosing the winner
    winner(user.total, AI.total, user.name, AI.name);
    return 0;
}