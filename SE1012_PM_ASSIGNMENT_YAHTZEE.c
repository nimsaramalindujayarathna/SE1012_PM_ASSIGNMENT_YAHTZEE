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
#include <termios.h>

// Normal text Colors
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Text Styles 
#define BOLD            "\033[1m"
#define DIM             "\033[2m"
#define ITALIC          "\033[3m"
#define UNDERLINED      "\033[4m"
#define BLINKING        "\033[5m"
#define HIGH_SCORE_TEXT "\033[1m\033[30m"  
#define HIGH_SCORE_BG   "\033[46m" 

// Reset Code
#define RESET "\033[0m"

// costant for dice readings
const char *diceFaces[6][5] = {
    { "┌───────┐", "│       │", "│   ●   │", "│       │", "└───────┘" },  // 1
    { "┌───────┐", "│ ●     │", "│       │", "│     ● │", "└───────┘" },  // 2
    { "┌───────┐", "│ ●     │", "│   ●   │", "│     ● │", "└───────┘" },  // 3
    { "┌───────┐", "│ ●   ● │", "│       │", "│ ●   ● │", "└───────┘" },  // 4
    { "┌───────┐", "│ ●   ● │", "│   ●   │", "│ ●   ● │", "└───────┘" },  // 5
    { "┌───────┐", "│ ●   ● │", "│ ●   ● │", "│ ●   ● │", "└───────┘" },  // 6
};

const char *combinationNames[13] = {
    "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes",
    "Three of a Kind", "Four of a Kind", "Full House",
    "Small Straight", "Large Straight", "Chance", "YAHTZEE"
};

typedef struct {
    char name[25];
    int dice[5];
    int scoredScore[13];
    int uScore;
    int lScore;
    int total;
    int combinations[13];
    int index;
}players;

////FUNCTION PROTOTYPE
int random_number();
int chance(int *dices);
int yahtzee(int *dices);
int fullHouse(int *dices);
int bonus(int numbersScore);
int fourOfaKind(int *dices);
int threeOfaKind(int *dices);
int largeStraight(int *dices);
int smallStraight(int *dices);
void next();
void instruct();
void important();
void clearInputs();
void timer (int time);
void AIName(char *name);
void editName(char *name);
void playerName(char *name);
void diceReadings(int *dices);
void smallToLarge(int *dices, int roll);
void AINumbers(int *dices, int index, int roll);
void AIDiceRoll(int *dices, int index, int roll);
void diceToSmall(int *dices, int roll, int *checkValue);
void CalScore(int *dices, int combinationNum, int *score);
void diceRollWithSingleIndex(int *dices, int index, int roll);
void smallRoll(int *dices, int roll, int num1, int num2, int num3);
void AIIndex(int *dices, int *comArray, int *AIIndex, int roundNo);
void winner(int userFinal, int AIFinal, char *playerName, char *AIName);
void printDice(int *dices, int lineBreak, int color, int time, int check);
void diceRollWithDoubleIndex(int *dices, int index1, int index2, int roll);
void scoreDisplay(char *name, int nScore, int oScore, int *total, int color);
void printScoresForUser(int *dices, int *combinationsArray, const char *com[]);
void scoreForCombination(int *dices, int *combination, int *score, char *name);
void AIscoreForCombination(int *dices, int combinationNum, int *score, char *name);
void AIComb(const char *com[],int *AIcombinationArray, char *AIname, int *AIScore, int AIn, int AIo);
void statistics(const char *com[], int *AIcombinationArray, int *AIdices, int *AInScore, int *AIoScore, int*AIScore);
void statRun(const char *com[],int *AIcombinationArray, int *AIdices, int *AInScore, int *AIoScore,char *AIName, int*AIScore);
void userIndex(int *dices, const char *com[], int *combinationArray, int *AIcombinationArray, int *combinationIndexNumber, char *name, char *AIname, int *Score, int*AIScore, int check, int n, int o, int AIn, int AIo);
void runningFun(int *dices, const char *com[], int *combinationArray, int *AIcombinationArray, int *combinationIndexNumberPointer, int *nScore, int *oScore, int *AIdices, int *AInScore, int *AIoScore, char *playerName, char *AIName, int *Score, int *AIScore);



////////FUNCTIONS DECLRATIONSBB
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
    printf(RESET"\nIf the length of the name is less than 20, Please press the enter button twice.\n");
    printf(CYAN"Enter the player's name (character limit 20): ");
    fgets(name, 24, stdin);
    editName(name);
    clearInputs();
}

void AIName(char *name) {
    //this function passes the AI name that is inputted by the user and passes it to the 
    //pointer addres of the sturcture as the parameter and also format the name before passing it.
    printf(RESET"If the length of the name is less than 20, Please press the enter button twice.\n");
    printf(RESET MAGENTA"Enter the AI's name (character limit 20): ");
    fgets(name, 24, stdin);
    editName(name);
    printf(RESET);
    clearInputs();
}


//outputs
int bonus(int numbersScore){
    //this functions parameters is the final score adn decides the bonus score and retunrs it 
    //occording to the upper combinations score
    return (numbersScore > 62)? 35:0;
}

void scoreDisplay(char *name, int nScore, int oScore, int *total, int color) {
    //this function parameters are the players name and there respective scores of upper and lower combinations
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
    //this function 's parameters are the final score and the names of the two players adn decides who won 
    //and prints the result
    printf("\n");
    if((userFinal > 230) && (AIFinal > 230) && (userFinal != AIFinal)) {
        printf(BOLD GREEN"You both Have performed Well. "RESET);
        if (userFinal != AIFinal){
            printf(BOLD GREEN"But there is only one WINNER."RESET);
        } else {
            printf(BOLD GREEN"Scores are Equal."RESET);
        }
    }
    printf("\n");
    if(userFinal < AIFinal){
        printf(BOLD MAGENTA"You tried your best but %s is just better."RESET, AIName);
    } else if(userFinal > AIFinal) {
        printf(BOLD CYAN"Congratulations, %s you have won the game."RESET, playerName);
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
        \nAfter each roll, you can choose to keep or re-roll any number of dice readings.\
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
    //obatained from chat gpt this function's functionality is to pause the execution of the program until
    // a key input is entered throught STDIN
    printf(DIM BOLD BLINKING"Proceed to the next round. Press anykey : "RESET);
    struct termios oldt, newt;
    // Save old terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // Set terminal to raw mode (disable echo and buffering)
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // Wait for a single key press
    getchar();
    // Restore old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}


//dice readings
int random_number(){
    // this function will generate random numbers from 1-6 for the dice readings
    return (rand() % 6) + 1;
} 

void diceReadings(int *dices) {
    // this fuction will store 5 randome numbers as dice readings when the each players dice array is passed as an argument
    for (int i = 0; i < 5; i++){
        dices[i] = random_number();
    }
}

void printDice(int *dices, int lineBreak, int color, int time, int check){
    int specialLocal = 0;
    int local = 1; // assign this variable to 0 basic numebers as dice readings, 1 if imaages for dice readings.
    /*this function will print the dice readings of the string that passes as the dices pointer. 
    if the linebreak value is one when calling the function prints a linebreak when printing the dice readings
    if the linebreak value is zero when calling the function, just print the dice readings
    time parameter is used to place a delay in print ing each dice reading. use 1 as argument if needde, if not need use 0 as argument.
    color argumenet is placed so that the dice reading colors are assigned occrding to the argument 1 if the dice readings is a Ai(magenta color)
    0 if dice readings are from human player (cyan color)*/
    if (check == 99) {
        local = 0;
    } else if (check == 9) {
        specialLocal = 1;
    }
    if (lineBreak == 1){
        printf("\n");
    }
    if (local == 0) {
        printf(ITALIC BOLD"Dice Readings are : " RESET);
            printf("[");
        if (color == 0) { //player
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
        } else if (color == 1) { // AI
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
    } else if (local == 1) {
        printf("\n");
        if (color == 0) { //player
            printf(CYAN);
        } else if (color == 1) { //AI
            printf(MAGENTA);
        }
        for (int row = 0; row < 5; row++) {  // Each dice face has 3 lines
            for (int i = 0; i < 5; i++) {
                printf("%s  ", diceFaces[dices[i] - 1][row]);
                timer(50);
            }
            printf("\n");  // New line after each row
        }
        if ((color == 0) && (specialLocal == 0)) {
            for (int i = 1; i < 6; i++) {
                printf(RESET BOLD" Index %d   "RESET, i );
            }
        }
        printf(RESET"\n");
    }
}

void diceRoll(int *dices, int *combinationsArray, const char *com[]) {
    // this function will roll the dice 3 times and get the readings according to the user's preference and the array which use to store the readings are passed as argument(pointer)
    char tempDices[5]; //tempary array to store temp dices
    int indexes; //indexs to keep
    int NoOfIndexes; // no of the indexes to keep
    char inputChar; //variable to check the the rolling condtion whether the user want to roll or not
    int i = 0;
    printf("\n\t\t      ");
    timer(450); //delay function
    printf(ITALIC BOLD"Roll NO %d" RESET ,i+1);// this selection print the roll no
    diceReadings(dices); //Inital dice roll
    printDice(dices, 0, 0, 1, 0); //Inital deice reads displayed
    printScoresForUser(dices, combinationsArray, com);
    for (i = 0; i < 2; i++) {
        int indexCheckArray[] = {0, 0, 0, 0, 0}; // this array is designed to stop the use from inputting the same index aagain and again
        //once the user enters the index the respective value will be 1 so when entering the next index the previous values are checked and 
        //promted the user occrodingly.
        timer(300);
        printf("If you want to roll the dices again       ");
        printf(RESET BOLD ITALIC "Press ---- 'Y'\n"RESET);
        timer(300);
        printf("If you do not want to roll again          ");
        printf(RESET BOLD ITALIC "Press ---- 'N'\n"RESET);
        timer(300);
        printf("Enter your decision : ");
        scanf(" %c",&inputChar);
        // input validation ---- inputChar
        while(!(inputChar == 'Y' || inputChar == 'y' || inputChar == 'N' || inputChar == 'n')){
            clearInputs();
            printf(BOLD RED BLINKING"Invalid input! Please press 'Y' to roll again or 'N' to stop rolling.\n"RESET);
            printf("Enter your decision : ");//if the inputs are wrong or invalid
            scanf(" %c",&inputChar);
        }
        clearInputs();
        if (inputChar == 'Y' || inputChar == 'y') { // condition to pass if the user want to roll again
            for (int j = 0; j < 5; j++ ) {
                tempDices[j] = dices[j]; //store the main array data to temp array to roll the dices again, while the values in the temp arrary are used to do the execution
            }
            diceReadings(dices); // next dice rolls. actually the programm roll the dice and store the prevous readings
            // in a temp array before asking the user what to do with the previous dice readings.
            timer(275);
            printf("Enter how many dice readings you want to keep before the next roll : ");
            //input validation ---- NoofIndexes
            while(1) {
                if (scanf("%d", &NoOfIndexes) != 1) { //check whethere the input is a interger value
                    printf(ITALIC YELLOW BLINKING"Invalid Input type. Please enter again. [0, 1, 2, 3, 4] : "RESET);
                    clearInputs();   
                    continue;
                }
                if ((NoOfIndexes < 0) || (NoOfIndexes > 4)) { // check whether the entered number of indexes are in the required reange
                    printf(BOLD RED BLINKING"Invalid number of indexes. Please enter again. [0, 1, 2, 3, 4] : "RESET);
                    clearInputs();   
                    continue;
                }
                clearInputs();
                break;
            }
            if (NoOfIndexes == 1) { // if the index number aare 1
                timer(275);
                printf("Enter the index number of the dice reading you wanted keep. (1 to 5)\n");
            } else if (NoOfIndexes > 1){ // if the idex numbers are more than 1
                timer(275);
                printf("Enter the index numbers of the dice readings you wanted keep. (1 to 5)\n");
            }
            for (int ii = 1; ii < NoOfIndexes + 1; ii++){
                timer(275);
                printf("Enter the index number %d (1 to 5): ", ii );
                while(1) {
                    if (scanf("%d", &indexes) != 1) { //  //check whethere the input is a interger value
                        printf(ITALIC YELLOW BLINKING"Invalid Input type. Please enter again. (1 to 5) : "RESET);
                        clearInputs();
                        continue;
                    }
                    if ((indexes < 1) || (indexes > 5)) { // check whether the indexes are in the required range
                        printf(BOLD RED BLINKING"Incorrect index enterd. Please enter again. (1 to 5) : "RESET);
                        clearInputs();
                        continue;
                    }
                    if (indexCheckArray[indexes - 1] == 1) { // specail case execeutes if the user enters the same index again which was preivouly entered.
                        printf(DIM GREEN"You entered the same index again. Please enter a different index. (1 to 5) : "RESET);
                        clearInputs();
                        continue;
                    }
                    break;
                }
                indexCheckArray[indexes -1] = 1; // when a index no is properly inputted the relevent index is assigned 1 in the array in order to check whether the same index is enterred again
                dices[indexes - 1] = tempDices[indexes - 1 ]; // the main array areday have the next dice rolls, so after the index nnumber is properly inputted through input validation,
                // the relevent index is copied from the temp array 
            }
            printf("\n\n\t\t      ");
            timer(600);
            printf(ITALIC BOLD"Roll NO %d" RESET ,i+2);// this prints the roll no
            if (NoOfIndexes != 0) {
                clearInputs();
            }
            printDice(dices, 0, 0, 1, 0); // print the changed and next dices rolls
            printScoresForUser(dices, combinationsArray, com); // this will print the score for every available combination accorind to the current dice readings
        } else if (inputChar == 'N' || inputChar == 'n') {
            break; // if the user do not want to roll again escape the function
        } 
    }
    timer(600);
    printf(BOLD ITALIC"\n\t\t      Final Dices" RESET);// after 3 dice rools or users's prefered dice rolls print  the dices
    printDice(dices , 0, 0, 0, 9); 
}


/*below functions are used to calculate the score for each lower combination when the dice readings are passed as an parameter.
the score is returned when calling the function*/
int chance(int *dices){
    // this function is deisigned to retunr the score for the dice readings if the selected combination is chances.
    //jjust retunr the sum of the dice readsings
    int sum = 0;
    for (int i = 0; i < 5;i++){
        sum = sum + dices[i];
    }
    return sum;
}

int yahtzee(int *dices){
    /*
    this function is deisigned to retunr the score for the dice readings if the selected combination is yahtzee.
    the first dice rading will be assigned to the temp values and check if the all the other readings were equal to that
    otherwise the retuning value will be 0 and the the execusion will be breaked from the for loop.
    */
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

int largeStraight(int *dices) {
    // this function is deisigned to retunr the score for the dice readings if the selected combination is large straight.
    // this will sort the dice readings checking the how many 1-6 numbers are available
    /*LOGIC
    if the dice readings were[3 4 2 4 5], then the array[] value will be this [0,1,1,2,1,0]
    this array[] will properly count how the dice readings area vavailable. 
    then check if the array readings are in these combination (1,2,3,4,5) or (2,3,4,5,6)
    then the relevent score is returned*/
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

int smallStraight(int *dices) {
    // this function is deisigned to retunr the score for the dice readings if the selected combination is small straight.
    // this will sort the dice readings checking the how many 1-6 numbers are available
    /*LOGIC
    if the dice readings were[3 4 2 4 5], then the array[] value will be this [0,1,1,2,1,0]
    this array[] will properly count how the dice readings area vavailable. 
    then check if the array readings are in these combination (1,2,3,4) or (2,3,4,5) or (3,4,5,6)
    then the relevent score is returned*/
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

int fullHouse(int *dices){
    // this function is deisigned to retunr the score for the dice readings if the selected combination is full house.
    // this will sort the dice readings checking the how many 1-6 numbers are available
    /*LOGIC
    if the dice readings were[3 4 2 4 5], then the array[] value will be this [0,1,1,2,1,0]
    this array[] will properly count how the dice readings area vavailable.
     then the 2 if statement in for loops will check if the same dice readings were avaialable 3 times and 2 times.
     if those two condition were checked true then the function returned the relvent score for full house.*/
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

int fourOfaKind(int *dices){
    // this function is deisigned to retunr the score for the dice readings if the selected combination is small straight.
    // this will sort the dice readings checking the how many 1-6 numbers are available
    /*LOGIC
    if the dice readings were[3 4 2 4 5], then the array[] value will be this [0,1,1,2,1,0]
    this array[] will properly count how the dice readings area vavailable. check if any value of the array[] is 4.
    then check and return the sum of the dice eradsings otherwise return 0 as the score*/
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

int threeOfaKind(int *dices){
    // this function is deisigned to retunr the score for the dice readings if the selected combination is small straight.
    // this will sort the dice readings checking the how many 1-6 numbers are available
    /*LOGIC
    if the dice readings were[3 4 2 4 5], then the array[] value will be this [0,1,1,2,1,0]
    this array[] will properly count how the dice readings area vavailable. check if any value of the array[] is 3.
    then check and return the sum of the dice eradsings otherwise return 0 as the score*/
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
void userIndex(int *dices, const char *com[], int *combinationArray, int *AIcombinationArray, int *combinationIndexNumber, char *name, char *AIname, int *Score, int *AIScore, int check, int n, int o, int AIn, int AIo){
    //this function is used to get the user's prefered combination for each dice rounds
    // arguments users dice readings, combination names string, combination array is used to pass and check the already selected combinations,
    // index number is used to calculate the score.
    int index;
    char spaces[] = {" "};
    if (check == 0) { // this condtion is specifically designed to print the relvent statemennt when printing. 
    //if the round is not the last round the first statemnt will print. unless prints otherstetmnet
        printf("\nCombinations Available to Choose.\n\n");
        timer(450);
    } else if (check == 1) {
        printf("\nAll the Combinations were used.\n\n");
        timer(450);
    }
    // this prints the currently available combinations for user to choose from.
    // the already selected comdition will be printed in dim format
    //also the upper combination and lower combination totla will be diaplyed for the player as well as the ai
    printf(BOLD"┌───────────────────────────────────────┬───────────────────────────────────────┐\n" RESET);
    printf(BOLD "│" RESET);
    printf(CYAN BOLD "   %20.20s's Combinations " RESET,name);
    printf(BOLD "│" RESET);
    printf(MAGENTA BOLD "   %20.20s's Combinations "RESET , AIname);
    printf(BOLD "│" RESET);
    printf("\n");
    printf(BOLD"├───────────────────────────────────────┼───────────────────────────────────────┤\n" RESET);
    // printf("\t    ");
    // printf(BOLD"│─────────────────────────────────────────────────────────────────────────│\n" RESET);
    for (int i = 0; i < 13; i++) { 
        if (i == 5) { // this if is impelemtneted to print the upper combinations total  with the respective combination
            printf(BOLD"│"RESET);
            printf("\t");
            if (combinationArray[i] == 0){
                printf("%2d. %-16s %3d ",(i+1),com[i],Score[i]);
                printf(BOLD CYAN"%3d"RESET, n);
            } else if (combinationArray[i] == 1){
                printf(DIM "%2d. %-16s %3d " RESET,(i+1),com[i], Score[i]);
                printf(BOLD CYAN"%3d"RESET, n);
            }
            printf("    ");
            printf(BOLD"│"RESET);
            printf("       ");
            if (AIcombinationArray[i] == 0){
                printf("%2d. %-16s %3d ", (i+1), com[i], AIScore[i]);
                printf(BOLD MAGENTA"%3d" RESET, AIn);
            } else if (AIcombinationArray[i] ==1) {
                printf(DIM"%2d. %-16s %3d " RESET,(i+1),com[i], AIScore[i]);
                printf(BOLD MAGENTA"%3d" RESET, AIn);
            }
            printf("    ");
            printf(BOLD"│"RESET);
            printf("\n");
        } else if (i == 12) { // this if is impelemtneted to print the lower combinations total  with the respective combination
            printf(BOLD"│"RESET);
            printf("\t");
            if (combinationArray[i] == 0){
                printf("%2d. %-16s %3d ",(i+1),com[i],Score[i]);
                printf(BOLD CYAN"%3d" RESET, o);
            } else if (combinationArray[i] == 1){
                printf(DIM "%2d. %-16s %3d " RESET,(i+1),com[i], Score[i]);
                printf(BOLD CYAN"%3d" RESET, o);
            }
            printf("    ");
            printf(BOLD"│"RESET);
            printf("       ");
            if (AIcombinationArray[i] == 0){
                printf("%2d. %-16s %3d ", (i+1), com[i], AIScore[i]);
                printf(BOLD MAGENTA"%3d" RESET, AIo);
            } else if (AIcombinationArray[i] ==1) {
                printf(DIM"%2d. %-16s %3d " RESET,(i+1),com[i], AIScore[i]);
                printf(BOLD MAGENTA"%3d" RESET, AIo);
            }
            printf("    ");
            printf(BOLD"│"RESET);
            printf("\n");
        }else { // this if is impelemtneted to print the combinations that dont need print the score.
            printf(BOLD"│"RESET);
            printf("\t");
            if (combinationArray[i] == 0){
                printf("%2d. %-16s %3d",(i+1),com[i],Score[i]);
            } else if (combinationArray[i] == 1){
                printf(DIM "%2d. %-16s %3d " RESET,(i+1),com[i], Score[i]);
            }
            printf("\t");
            printf(BOLD"│"RESET);
            printf("\t");
            if (AIcombinationArray[i] == 0){
                printf("%2d. %-16s %3d", (i+1), com[i], AIScore[i]);
            } else if (AIcombinationArray[i] ==1) {
                printf(DIM"%2d. %-16s %3d" RESET,(i+1),com[i], AIScore[i]);
            }
            printf("\t");
            printf(BOLD"│"RESET);
            printf("\n");
        } 
    }
    timer(500);
    //total score will also be displayed there for both the players
    printf(BOLD"├───────────────────────────────────────┼───────────────────────────────────────┤\n" RESET);
    printf(BOLD"│"RESET);
    printf("           ");
    printf(BOLD UNDERLINED CYAN"Current Total Score: %3d" RESET , o + n);
    printf("    ");
    printf(BOLD"│"RESET);
    printf("           ");
    printf(BOLD UNDERLINED MAGENTA"Current Total Score: %3d" RESET , AIo + AIn);
    printf("    ");
    printf(BOLD"│"RESET);
    printf("\n");
    printf(BOLD"└───────────────────────────────────────┴───────────────────────────────────────┘\n" RESET);
    printf("\n\n");
    if (check == 1) {
        //this is placed so the if the round no is after 13  this function will stop from here.
        return;
    }
    diceRoll(dices, combinationArray, com); // this will run the dicerolling 
    //after that the user is prometed to enter the combination number
    //input validation for indexI variable
    while (1) {
        printf(BOLD"\n   Choose an available combination no (1 to 13): "RESET);
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
    combinationArray[index - 1] = 1; // after validating the combination number the selected combinations is check as selected in the array.
    //so that the same index wouldn't be able to enter again.
    *combinationIndexNumber = index;// returning the users prefened comabintion number as a pointer 
    clearInputs();
}

void scoreForCombination(int *dices, int *combinationNum, int *score, char *name){
    //this function will produce the score when the combination type is inputted as a interger value
    //parameters respcetives players dice readings, combinations seleceted by the user or AI, pointer to retuen the score to the struct
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
    *score = tempscore; // the score for the respective combination is retuned through a pointer 
    printf("Score : ");
    timer(350);
    printf(CYAN BOLD "%d\n"RESET, tempscore);
    timer(350);
}

void AIscoreForCombination(int *dices, int combinationNum, int *score, char *name){
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
    printf("Score : ");
    timer(350);
    printf(MAGENTA BOLD "%d\n\n"RESET, tempscore);
    timer(350);
}

void CalScore(int *dices, int combinationNum, int *score){
    /// this function will produce the score when the combination type is inputted - for the AI
    // you might see this function is similar with the prevous functions while above two functions are seperately designed to calculate score for the player and AI sperately.
    //but this function is specfically designed to get the all the score for all the combination when proceesing the AI. The Ai need to use the scores for every available combination
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

void printScoresForUser(int *dices, int *combinationsArray, const char *com[]) {
    // this function is designed to print the the score for each available combination accoring to the current dice readings.
    int sscores[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int maxScore = 0;
    for (int i = 0; i < 13; i++) { //calculate score.
            CalScore(dices, i + 1, &sscores[i]);
    }
    printf("\n");
    printf(UNDERLINED"Score for every Combination availabel for the current dice Readings"RESET);
    printf("\n\n");
    for (int i = 0; i < 13; i++) {
        //check the higherest score.
        if ((combinationsArray[i] == 0) && (maxScore < sscores[i])){
            maxScore = sscores[i];
        }
    }
    printf("\t\t");
    printf(BOLD"┌─────────────────────────┐\n" RESET);
    for (int i = 0; i < 13; i++) {
        if (combinationsArray[i] == 0){ // highlight the highest score 
            printf("\t\t");
            printf(BOLD"│ "RESET);
            if((sscores[i] == maxScore)  && (!(maxScore == 0))) {
                timer(125);
                printf(HIGH_SCORE_BG HIGH_SCORE_TEXT"%2d. %-16s %2d"RESET, i+1, com[i], sscores[i]);
            } else {
                timer(125);
                printf("%2d. %-16s %2d", i+1, com[i], sscores[i]);
            }
            printf(BOLD " │"RESET);
            printf("\n");
        }
    }
    printf("\t\t");
    printf(BOLD "└─────────────────────────┘"RESET);
    printf("\n\n");
}

void runningFun(int *dices, const char *com[], int *combinationArray, int *AIcombinationArray, int *combinationIndexNumberPointer, int *nScore, int *oScore, int *AIdices, int *AInScore, int *AIoScore, char *playerName, char *AIName, int *Score, int *AIScore){
    //this is the second top priority functions of the game, this function will loop 13 rounds of the game.
    //there are many arguments to this function, all the other functions are called inside this function.
    //such as every deails of the player and the AI,combinations names, dices readings, userprefferd combination no
    int tempscore; // score for the respective condition
    int AItempscore; // score for the respective AI combination
    int sum1 = 0; //to score the upper combination totla for human player locally
    int sum2 = 0; //to score the lower combination totla for human player locally
    int AIsum1 = 0; //to score the upper combination totla for AI player locally
    int AIsum2 = 0; //to score the lower combination totla for AI player locally
    int AIIndexNum; 
    int playerIndex;
    for (int i = 0; i < 13; i++) {
        Score[i] = 0;
        AIScore[i] = 0;
        combinationArray[i] = 0;
        AIcombinationArray[i] = 0;
    } //zeroing the comabination arrays and scores arrays.
    for (int i = 0; i < 13; i++) {
        printf(BOLD ITALIC"\n\n\n**********************************  Round No %d  **********************************\n"RESET,i+1);    //print the rpund number
        //if you are running the statistics function comment the below line
        userIndex(dices,com ,combinationArray, AIcombinationArray, combinationIndexNumberPointer, playerName,AIName, Score, AIScore, 0, sum1, sum2, AIsum1, AIsum2);
        //this runs the dice rolls and enterint the combination number
        printf(DIM"──────────────────────────────────────────────────────────────────────────────────\n"RESET);
        diceReadings(AIdices); // intial roll of Ai's dices
        printf("\n\t");
        printf(BOLD MAGENTA"%20.20s's dice readings\n\n"RESET,AIName);
        timer(350);
        printf(BOLD ITALIC"\n\t\t      Roll NO 1 "RESET);
        timer(250);
        printDice(AIdices, 0, 1, 1, 0);
        AIIndex(AIdices, AIcombinationArray, &AIIndexNum, i); // this decides which index to choose according to the dice readings, aslo rooll the dices for much better dice readings.
        printf(DIM"\n──────────────────────────────────────────────────────────────────────────────────"RESET);
        printf(BOLD ITALIC"\n\n\t\t%s's Final "RESET,playerName);//below code block shows the huma players final dice readings combination choosed score for the round.
        timer(425);
        printDice(dices, 0, 0, 0, 99);
        printf("\t\tCombination Type : " );
        timer(350);
        printf(BOLD CYAN"%-16s\t"RESET ,com[*combinationIndexNumberPointer - 1]);
        timer(425);
        scoreForCombination(dices, combinationIndexNumberPointer, &tempscore, playerName);
        timer(500);
        if (*combinationIndexNumberPointer < 7) { //update the relevent scores for the human player.
            sum1 = sum1 + tempscore;
        } else {
            sum2 = sum2 + tempscore;
        }
        playerIndex = *combinationIndexNumberPointer;
        Score[playerIndex - 1] = tempscore;
        printf(BOLD ITALIC"\n\t\t%s's Final "RESET,AIName); //below code block shows the huma players final dice readings combination choosed score for the round.
        timer(425);
        printDice(AIdices, 0, 1, 0, 99);
        printf("\t\tCombination Type : ");
        timer(350);
        printf(BOLD MAGENTA"%-16s\t"RESET, com[AIIndexNum]);
        timer(425);
        AIscoreForCombination(AIdices, AIIndexNum + 1, &AItempscore, AIName);
        timer(500);
        if (AIIndexNum+1 < 7) {  //update the relevent scores for the human player.
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
    *AIoScore = AIsum2; //update all the scores after 13 rounds.
    userIndex(dices,com ,combinationArray, AIcombinationArray, combinationIndexNumberPointer, playerName,AIName, Score, AIScore, 1, sum1, sum2, AIsum1, AIsum2); // this function will only show the respective scores
    //aslo this function will not execute dicerools because of the argument "0" passed.
}


//Ai functions
void AIIndex(int *dices, int *comArray, int *AIIndex, int roundNo) {
    // this is the main function that implements the AI.
    // parameter are the AI's dice readings, combination check array to check which combinations were selected, respective index no for the selected combination is pointed to a variable where it is called.
    // this function will choose the best combination out of the available combinations by comparing the scores for each combination
    // also inside this function fi there are 3same dice reading they rolled agan in order to obtain a four of akind or a yahtzee, vi versa for the 4 same dices redaings.
    int scores[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int index;//a deafult assigned value to check after the function exceute to check if this variable was changed after the execution
    int scorecheck = 0;
    int sortNumber = 0;
    int chancesVariable = 0;
    int checkNumber = 0;
    for (int l = 0; l < 3; l++) {// round number for the Ai
        index = 99;//a deafult assigned value to check if it changes  after the below statement execution
        int sortedArray[] = {0, 0, 0, 0, 0, 0}; 
        for (int i = 0; i < 5; i++) { 
        // this will sort the dice readings checking the how many 1-6 numbers are available
        /*if the dice readings were[3 4 2 4 5], then the sotedarray[] value will be this [0,1,1,2,1,0]*/
            sortedArray[dices[i] - 1]++ ;
        }
        for (int i = 0; i < 6; i++) { //check whether if there are same 3 or 4 dice readings. if assign that dice readings to the sort number varialbe.
            if (sortedArray[i] == 4 || sortedArray[i] == 3) {
                sortNumber = sortedArray[i];
            }
        }
        for (int i = 0; i < 13; i++) {
            CalScore(dices, i + 1, &scores[i]); // calculate the score for 13 combinations
        }
        int temp = 0;
        for (int i = 0; i < 13; i++) {
            if (comArray[i] == 0) {
                if (i == 11) { // skipping chances combination until 11+ round
                    continue;
                } 
                if (temp < scores[i]) { //finding the maximum score 
                    temp = scores[i];
                    index = i;
                    if (i == 12) { //prioritising the yahtzee and full house combinations.
                        // if ((comArray[5] == 0) && (dices[1] == 6)) {
                        //     // this condition set the Ai choosen index to sixes if the dices were all containsing 6's
                        //     //this will stop the dice readings from assiging to yahtzee
                        //     index = 5;
                        // }
                        goto end1;
                    }
                    if (i == 8) { // break fullhouse
                        goto end1;
                    }
                } else if (temp == scores[i] && (i == 6 || i == 7)) { //when checking the highest score if there are same score for 
                //other combinations and the those combinations are fpur of a kinfd or three of a kind the selected index for the Ai will be those combinations
                    index = i;
                }
            }
        }
        if ((index == 10) && (scores[index] != 0)) { //this condition is placed here to stop further checks if the dice have scored for the largeStraight
            goto end1;
        }
        if ((index == 9) && (comArray[10] == 1)) { //this condition is placed here to stop further checks and pass the combination as small straight if the large staright combination already scored.
            goto end1; 
        }
        if (l < 2){ //check if there are any left rolls for the AI
            if ((index == 9) && (comArray[10] == 0)) { 
                //if the large straight combination is not scored yet and the diecs have a small straight 
                // then the dices will be rolled again in order to obtain a large straight.
                smallToLarge(dices, l);
                continue;
            }
            if(comArray[12] == 0 || comArray[6] == 0 || comArray[7] == 0) {
                if (sortNumber == 3) { //if there are same 3 dice readings using the below function the dices will be rolled again to obtain more same dice readings
                    //printf("Entering 3s");
                    AIDiceRoll(dices, 6, l);
                    continue;
                }
                if (sortNumber == 4) { //if there are same 4 dice readings using the below function the dices will be rolled again to obtain more same dice readings
                    //printf("Entering 4s");
                    AIDiceRoll(dices, 7, l);
                    continue;
                }
            }
            if (index < 6) { // if the sleceted combination is a upper combination the dices are rolled again in order to obatain more of the same dice readings.
                //printf("Entering number- %d", index+1);
                checkNumber = 0;
                if ((comArray[9] == 0) && (l == 0)) { //checks if smal straight is not yet used and there are 2 remaining rolls left
                    int localCheck = 0;
                    for (int i = 0; i < 6; i++) { 
                        if ((sortedArray[i] > 1) && comArray[i] == 0) { // use sorted array to check if there are 2 or more same readings and the respective number is not yet assigned
                            localCheck = 1;//this will stop executing the diceToSmall function.
                        }
                    }
                    if (localCheck == 0) {
                        diceToSmall(dices,  l, &checkNumber); // this function will try to obtain a small straight if  the dices have a chance of obtaining it after a roll
                    }
                }
                if (checkNumber == 0) { // roll the numbers
                    AINumbers(dices, index, l);
                }
                continue;
            }
            if (roundNo >= 11 && comArray[11] == 0) { //chances in the end
                //printf("Entering chances");
                // this condtions runs when the round number is 12 or 13 and the chances combinations is not yet checked.
                //this code will find the maximum available dice value and roll the dices keeping that value.
                index = 11;
                if (chancesVariable == 0){
                    for (int c = 6; c > 0; c--){
                        if(sortedArray[c - 1] > 0){
                            chancesVariable = c - 1; //finding the highest dice value in the dice readings.
                            break;
                        }
                    }
                }
                AINumbers(dices, chancesVariable, l);
            }
            if (roundNo == 12 && comArray[12] == 0) { //yahtzee at the last
                //this if contions only runs if the yahtzee combination is not yet assigned.
                //from this the code selectes the most available dice readings and rolling the dice reading keeping that value.
                //printf("Entering Yahtzee");
                index = 12;
                int tempo = 0;
                int maxi,indexi;
                for (int c = 0; c < 6; c++){
                    if (tempo < sortedArray[c]){
                        tempo = sortedArray[c];
                        indexi = c; //finding the most repeated value in the dice readings.
                    }
                }
                AINumbers(dices, indexi, l);
            }
        }
        if (index == 99) { // if the index is not assigned after executing above code(this happens if the maximum score is not assigned)
        // zero for all the combintaions. assign the next available combination.
            //printf("Entering 99");
            for (int i = 0; i < 13; i++) {
                if (comArray[i] == 0) {
                    index = i;
                    switch (l) { //roll the dices fully if no combination is available
                        case 0:
                            diceReadings(dices);
                            timer(350);
                            printf(BOLD ITALIC"\n\t\t      Roll NO 2 "RESET);
                            timer(250);
                            printDice(dices,0, 1, 1, 0);
                            break;
                        case 1:
                            diceReadings(dices);
                            timer(350);
                            printf(BOLD ITALIC"\n\t\t      Roll NO 3"RESET);
                            timer(250);
                            printDice(dices,0, 1, 1, 0);
                            break;
                        default:
                            break;
                    }
                    break;;
                }
            }
        }
    }
    if ((scores[index] == 0) && (comArray[11] == 0)){
        //printf("Entering chances if 0");
        index = 11;
    }
    if ((index == 7) || (index == 6))  { 
        int sortedArray[] = {0, 0, 0, 0, 0, 0}; 
        int diceof4, diceof3;
        for (int i = 0; i < 5; i++) { 
        // this will sort the dice readings checking the how many 1-6 numbers are available
        /*if the dice readings were[3 4 2 4 5], then the sotedarray[] value will be this [0,1,1,2,1,0]*/
            sortedArray[dices[i] - 1]++ ;
        }
        for (int i = 0; i < 6; i++) { 
            if(sortedArray[i] == 4) {
                diceof4 = i + 1;
            }
            if(sortedArray[i] == 3) {
                diceof3 = i + 1;
            }
        }
        if ((comArray[5] == 0) && (diceof4 == 6)) { //four of a kind
            // this condition set the Ai choosen index to sixes if the dices were all containsing 6's
            //this will stop the dice readings from assiging to yahtzee
            index = 5;
        }
        if ((comArray[5] == 0) && (diceof3 == 6)) {  //three of a kind
            // this condition set the Ai choosen index to sixes if the dices were all containsing 6's
            //this will stop the dice readings from assiging to yahtzee
            index = 5;
        }
    }
    end1:
    comArray[index] = 1; // removing the selected combination 
    *AIIndex = index;  //assigning the  selected combination index.
}

void AIDiceRoll(int *dices, int index, int roll) {
    // this function is designed to roll the Ai dice reaings, if only one dice is needed to be rolled.
    // parameteres are the AI dices index which the dice reaings should roll, and the roll no to display
    // if the index is 6 it will run the singleindex function which can only roll 1 dice.
    // if the inedx is 7 it will run the double index function which can roll upto 2 dice readings.
    int singleNumber, indexNo, index1, index2;
    int sortedArray[] = {0, 0, 0, 0, 0, 0}; 
    for (int i = 0; i < 5; i++) {
        sortedArray[dices[i] - 1]++ ;
    }
    if(index == 7) { //checking whether the dices are needed to change 1 reading
        for (int i = 0; i < 5; i++) {
            if (sortedArray[i] == 1) { // find the dice reading which is only once rolled out of the 4 same dices.
                singleNumber = i + 1;
                break;
            }
        }
        for (int i = 0; i < 5; i++) { // find the inedx of that value
            if (dices[i] == singleNumber) {
                indexNo = i;
                break;
            }
        }
        diceRollWithSingleIndex(dices, indexNo, roll); // only roll that unequal dice readings.
    }
    if (index == 6) { //checking whether the dices are needed to change 2 reading
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
        } // the above 2 for loops will find the 2 differnte dice readings indexes if there are 3 same dice readings
        diceRollWithDoubleIndex(dices, index1, index2, roll); // roll the 2 unmatching indexs
    }
}

void diceRollWithSingleIndex(int *dices, int index, int roll) {
    // this function is designed to roll the Ai dice reaings, if only single dice is needed to be rolled.
    // parameteres are the AI dices indexes which the dice readings should roll, and the roll no to display
    int tempArray[] = {0, 0, 0, 0, 0}; 
    for (int i = 0; i < 5; i++) {//assigning the dice readings to a temp array.
        tempArray[i] =  dices[i];
    }
    diceReadings(dices);
    for (int i = 0; i < 5; i++) {
        if (i == index){
            continue;
        } 
        dices[i] =  tempArray[i];
    } //assigning dice readings from the temp array to dice readings except for the  index to change.
    switch (roll) { //checking which diec roll this was
        case 0:
            timer(350);
            printf(BOLD ITALIC"\n\t\t      Roll NO 2"RESET);
            timer(250);
            printDice(dices, 0, 1, 1, 0);
            break;
        case 1:
            timer(350);
            printf(BOLD ITALIC"\n\t\t      Roll NO 3"RESET);
            timer(250);
            printDice(dices, 0, 1, 1, 0);
            break;
        default:
            break;
    }
}

void diceRollWithDoubleIndex(int *dices, int index1, int index2, int roll) {
    // this function is designed to roll the Ai dice reaings, if only two dices are needed to be rolled.
    // parameteres are the AI dices indexes which the dice readings should roll, and the roll no to display
    int tempArray[] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) { //assigning the dice readings to a temp array.
        tempArray[i] =  dices[i];
    }
    diceReadings(dices);
    for (int i = 0; i < 5; i++) {
        if (i == index1 || i == index2){
            continue;
        } 
        dices[i] =  tempArray[i];
    }  //assigning dice readings from the temp array to dice readings except for the 2 indexes to change.
    switch (roll) { //checking which diec roll this was
        case 0:
            timer(350);
            printf(BOLD ITALIC"\n\t\t      Roll NO 2"RESET);
            timer(250);
            printDice(dices, 0, 1, 1, 0);
            break;
        case 1:
            timer(350);
            printf(BOLD ITALIC"\n\t\t      Roll NO 3"RESET);
            timer(250);
            printDice(dices, 0, 1, 1, 0);
            break;
        default:
            break;
    }
}

void AINumbers (int *dices, int index, int roll) {
    // this function is designed to roll the dices again if the best combination is choose as a upper combination.
    // this function will try to rolll the dices again to get more of the same number which is choosn for the combination.
    int tempArray[] = {0, 0, 0, 0, 0};
    int diceNumber = index + 1;
    // printf("Running number - %d\n", diceNumber);
    for (int i = 0; i < 5; i++) { //assigning the dice readings to a temp array.
        if (dices[i] == diceNumber) {// assign only the dice which is passed to the function.otherwise  those temp array readings will be 0
            tempArray[i] = dices[i];
        }
    }
    diceReadings(dices); //rolling a new dice roll
    for (int i = 0; i < 5; i++) {
        if (tempArray[i] != 0) { // assigne the dice array with those dices after rolling again.
            dices[i] = tempArray[i];
        }
    }
    switch (roll) { //chech roll number
        case 0:
            timer(350);
            printf(BOLD ITALIC"\n\t\t      Roll NO 2"RESET);
            timer(250);
            printDice(dices, 0, 1, 1, 0);
            break;
        case 1:
            timer(350);
            printf(BOLD ITALIC"\n\t\t      Roll NO 3"RESET);
            timer(250);
            printDice(dices, 0, 1, 1, 0);
            break;
        default:
            break;
    }
}

void smallToLarge (int *dices, int roll) {
    //this function will roll the dices again in order to obtain a large straight if the dices already have a small straight.
    // parameters are the dices and the current roll number of the AI   
    int thereIsTwo = 0;
    int valueTwo;
    int rollValue;
    int index;
    int sortedArray[] = {0, 0, 0, 0, 0, 0}; 
    for (int i = 0; i < 5; i++) { 
    // this will sort the dice readings checking the how many 1-6 numbers are available
    /*if the dice readings were[3 4 2 4 5], then the sotedarray[] value will be this [0,1,1,2,1,0]*/
        sortedArray[dices[i] - 1]++ ;
    }
    for (int i = 0; i < 6; i++) { //using the sorted dice readings check whethere if there are any repeated dice readings.
    //if there are 2 same readings, there is a chance in obtaining large straight if one of those dice was rolled
        if(sortedArray[i] == 2){
            thereIsTwo  = 1;
            valueTwo = i + 1;
        }
    }
    if (thereIsTwo == 0){
        //if there is no same readings, there is only 1,2,3,4 or 3,4,5,6 small straights
        //if its a 1,2,3,4 the other reading will be 6, vis versa 3,4,5,6 the other reading will be 1 
        for (int i = 0; i < 5; i++) { 
            //find which type of a small straight from the above 2
            if (dices[i] == 2) {
                rollValue = 6;
            } else if(dices[i] == 5) {
                rollValue = 1;
            }
        }
        for (int i = 0; i < 5; i++) { 
            //after finding that value find the respective index of that reading
            if ((rollValue == 1) && (dices[i] == 1)) {
                index = i;
            } 
            if ((rollValue == 6) && (dices[i] == 6)) {
                index = i;
            }
        }
        diceRollWithSingleIndex(dices, index, roll); // roll the index of that value
    } else if (thereIsTwo == 1) { // if there are 2 repeated dice readings roll one of those repeated dices in order to obtain a large straight.
        for (int i = 0; i < 5; i++) { 
            if (valueTwo == dices[i]) {
                index = i;
            }
        }
        diceRollWithSingleIndex(dices, index, roll);// roll the one of index from the same dices.
    }
}

void diceToSmall (int *dices, int roll, int *checkValue) {
    //this function is used to check if there is any chance to obtain a small straight from the current dices after a roll.
    //check whethere the dices have 3 consecative readings.
    // if there are 3 consecative readings it will run the respective index to roll
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    int condition; 
    int indexs[2];
    int index = 0;
    *checkValue = 1;
    int array[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        array[dices[i] - 1]++ ;
    }
    if(array[0] >= 1 && array[1] >= 1 && array[2] >= 1) { //check 1,2,3
        smallRoll (dices, roll, 1, 2, 3);
    } else if (array[1] >= 1 && array[2] >= 1 && array[3] >= 1) { //check 2,3,4
        smallRoll (dices, roll, 2, 3, 4);
    } else if (array[2] >= 1 && array[3] >= 1 && array[4] >= 1) { //check 3,4,5
        smallRoll (dices, roll, 3, 4, 5);
    } else if (array[3] >= 1 && array[4] >= 1 && array[5] >= 1) { //check 4,5,6
        smallRoll (dices, roll, 4, 5, 6);
    } else {
        *checkValue = 0;
        return;
    }

}

void smallRoll (int *dices, int roll, int num1, int num2, int num3) {
    // this function is designed to roll the dices in order to obatin a small straight 
    // the 2 dices that are needed to be rolled in order to obatin a smalls straight will be found after after executing this and 
    // the 2 indexes will passed as parameters in the diceRollWithDouble Index function
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    int indexs[2];
    int index = 0;
    for (int i = 0; i < 5; i++) {
            if ((dices[i] == num1) && (temp1 == 0)){
                temp1 = 1;
            }else if ((dices[i] == num2) && (temp2 == 0)){
                temp2 = 1;
            }else if ((dices[i] == num3) && (temp3 == 0)){
                temp3 = 1;
            } else {
                indexs[index++] = i;
            }
        }
        diceRollWithDoubleIndex(dices, indexs[0], indexs[1], roll);
}


//other mini functions used for the input validation of the game and delays
void clearInputs() {
    // this function is used to get the inputs in the correct data type.
    int input;
    while ((input = getchar()) != '\n' && input != EOF);  // remove leftover inputs in the input buffer memory and clear other inputs EOF - end of file
}

void timer (int time) {
    //this function is specifically designed to add delays when executing the game.
    //the parameter passsthe time which need to be delayed in miliseconds
    fflush(stdout);
    usleep(time * 1000);
}


//find the AI's Statistics
void statistics(const char *com[],int *AIcombinationArray, int *AIdices, int *AInScore, int *AIoScore,  int*AIScore) {
    //this function is specifically designed to runn the game only for the AI  as much as reuired amount of rounds in order to get the stats on how the AI scores.
    // this function will print the average scores and the percentage which the bonus were abotained by th AI
    int check;
    printf("Press,\t0 if high/low avg check\n\t1 if percentage check,\n\t2 if cutoff check,\n\t3 if Combination Percentage\t\t: ");
    scanf("%d", &check);
    if (check == 3){//combiantion percentage check
        float scores[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        float avgscores[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int loop;
        int sum = 0;
        printf("Enter amount of loops: ");
        scanf("%d", &loop);
        float loopnum = loop;
        for (int ii = 0; ii < loop; ii++){
            statRun(com,AIcombinationArray,AIdices,AInScore,AIoScore,"AI Player", AIScore);
            for (int i = 0; i < 13; i++){
                if (i < 6 || i == 11){
                    scores[i] += AIScore[i];
                } else {
                    if (AIScore[i] > 0){
                        scores[i]++;
                    }
                }
            }
        }  
        for (int i = 0; i < 13; i++){
            if (i < 6 || i == 11){
                avgscores[i] = scores[i] / loopnum;
            } else {
                avgscores[i] = (scores[i] / loopnum) * 100;
            }
        }
        printf("Average for Ones     %5.2f\n",avgscores[0]);
        printf("Average for Twos     %5.2f\n",avgscores[1]);
        printf("Average for Thress   %5.2f\n",avgscores[2]);
        printf("Average for Fours    %5.2f\n",avgscores[3]);
        printf("Average for Fives    %5.2f\n",avgscores[4]);
        printf("Average for Sixes    %5.2f\n",avgscores[5]);
        printf("Average for Chances  %5.2f\n",avgscores[11]);
        printf("Three of a kind Percentage  %5.2f\n",avgscores[6]);
        printf("Four of a kind Percentage   %5.2f\n",avgscores[7]);
        printf("Full House Percentage       %5.2f\n",avgscores[8]);
        printf("Small Straight Percentage   %5.2f\n",avgscores[9]);
        printf("Large Straight Percentage   %5.2f\n",avgscores[10]);
        printf("Yahtzee Percentage          %5.2f\n",avgscores[12]);
    }
    if (check == 2){//cutoff marks check
        int loop;
        int scorecut;
        int interval;
        int cutoff[100];
        float result[100];
        float percentageresult[100];
        int count = 0;
        printf("Enter amount of loops: ");
        scanf("%d", &loop);
        float loopnum = loop;
        printf("Enter score cut off: ");
        scanf("%d", &scorecut);
        printf("Enter interval: ");
        scanf("%d", &interval);
        FILE *text = fopen("text.txt", "w");
        for(; scorecut > 0; scorecut-=interval){ //skips the intialization of the variable for the for loop becuase scorecount is already intialized.
            int sum = 0;
            float cutcount = 0;
            for (int ii = 0; ii < loop; ii++){
                statRun(com,AIcombinationArray,AIdices,AInScore,AIoScore,"AI Player", AIScore); 
                sum = *AInScore + *AIoScore;
                if(scorecut <= sum) {
                    cutcount++;
                }
            } 
            float cutpercentage = (cutcount / loopnum) * 100;
            cutoff[count] = scorecut;
            result[count] = cutcount;
            percentageresult[count] = cutpercentage;
            count++;
            fprintf(text, "Cutoff Score is %3d,\tCutoff Count is %3.0f,\tCutoff Percentage is %5.2f\n", scorecut, cutcount, cutpercentage);
        }
        for (int i = 0; i < count; i++) {
            printf("Cutoff Score is %3d,\tCutoff Count is %3.0f,\tCutoff Percentage is %5.2f\n", cutoff[i], result[i], percentageresult[i]);
        }
        fclose(text); 
    }
    if (check == 1){// score avergae,bonus percentage
        int loop;
        int upper = 0;
        int lower = 0;
        float bonus = 0;
        int bonusScore = 0;
        int total = 0;
        int sum = 0;
        int finalforcurent = 0;
        int totalFinal = 0;
        printf("Enter amount of loops: ");
        scanf("%d", &loop);
        float loopnum = loop;
        for (int ii = 0; ii < loop; ii++){
            statRun(com,AIcombinationArray,AIdices,AInScore,AIoScore,"AI Player", AIScore);
            upper += *AInScore;
            lower += *AIoScore;
            sum = *AInScore + *AIoScore;
            total += sum;
            if(*AInScore > 63) {
                bonus++;
                bonusScore = 35;
            } else {
                bonusScore = 0;
            }
            finalforcurent = bonusScore + sum;
            totalFinal += finalforcurent;
        }   
        float avgupper = upper / loopnum;
        float avglower = lower / loopnum;
        float avgtotal = total / loopnum;
        float avgbonus = bonus / loopnum;
        float avgfinal = totalFinal / loopnum;
        float percentage = (bonus / loopnum) * 100;
        printf("Total of upper scores is %7d, for %6.0f simulations. Average of upper score is  %7.2f\n", upper, loopnum, avgupper);
        printf("Total of lower scores is %7d, for %6.0f simulations. Average of lower score is  %7.2f\n", lower, loopnum, avglower);
        printf("Total of total scores is %7d, for %6.0f simulations. Average of total score is  %7.2f\n\n", total, loopnum, avgtotal);
        printf("Total of Final scores is %7d, for %6.0f simulations. Average of Final score is  %7.2f\n\n", totalFinal, loopnum, avgfinal);
        printf("Number of bonuse's are  %4.0f,    Bonus Percentage is    %5.2f\n",bonus, percentage );
    }
    if (check == 0){//highscore lower score average.
        int scores;
        int testCases;
        int count = 0;
        float hightotal = 0;
        float lowtotal = 0;
        printf("Enter amount of test cases: ");
        scanf("%d", &testCases);
        printf("Enter amount of scores to make the average: ");
        scanf("%d", &scores);
        float loopnum = scores;
        for(int i = 0; i< scores; i++){ 
            int highscore = 0;
            int lowerscore = 10000;
            int sum = 0;
            float cutcount = 0;
            for (int ii = 0; ii < testCases; ii++){
                statRun(com,AIcombinationArray,AIdices,AInScore,AIoScore,"AI Player", AIScore); 
                sum = *AInScore + *AIoScore;
                if(highscore < sum) {
                    highscore = sum;
                }
                if(lowerscore > sum) {
                    lowerscore = sum;
                }
            }   
            hightotal += highscore;
            lowtotal += lowerscore;
        }
        float avghigh = hightotal / loopnum;
        float avglow = lowtotal / loopnum;
        printf("Average of highest scores is  %7.2f, for %6.0f simulations.\n", avghigh, loopnum);
        printf("Average of lowest scores is   %7.2f, for %6.0f simulations.\n", avglow, loopnum);
    }
}

void statRun(const char *com[], int *AIcombinationArray,  int *AIdices, int *AInScore, int *AIoScore, char *AIName, int*AIScore){
    int AItempscore; // score for the respective AI combination
    int AIsum1 = 0; //to score the upper combination totla for AI player locally
    int AIsum2 = 0; //to score the lower combination totla for AI player locally
    int AIIndexNum; 
    for (int i = 0; i < 13; i++) {
        AIScore[i] = 0;
        AIcombinationArray[i] = 0;
    } //zeroing the comabination arrays and scores arrays.
    for (int i = 0; i < 13; i++) {
        printf("Round No %d\n",i+1);   
        printf(BOLD ITALIC"\tRoll NO (1) - "RESET);
        diceReadings(AIdices); // intial roll of Ai's dices
        printDice(AIdices, 0, 1, 1, 99);
        AIIndex(AIdices, AIcombinationArray, &AIIndexNum, i); // this decides which index to choose according to the dice readings, aslo rooll the dices for much better dice readings.
        AIscoreForCombination(AIdices, AIIndexNum + 1, &AItempscore, AIName);
        if (AIIndexNum+1 < 7) {  //update the relevent scores for the human player.
            AIsum1 = AIsum1 + AItempscore;
        } else {
            AIsum2 = AIsum2 + AItempscore;
        }               
        AIScore[AIIndexNum] = AItempscore;
    }
    *AInScore = AIsum1;
    *AIoScore = AIsum2; //update all the scores after 13 rounds.
    AIComb(com,AIcombinationArray, "AI Player",AIScore, AIsum1, AIsum2);//aslo this function will not execute dicerools because of the argument "0" passed.
}

void AIComb(const char *com[],int *AIcombinationArray, char *AIname, int*AIScore, int AIn, int AIo){
    //this function is used to get the user's prefered combination for each dice rounds
    // arguments users dice readings, combination names string, combination array is used to pass and check the already selected combinations,
    // index number is used to calculate the score.
    int index;  
    printf("%20s's Combinations\n", AIname);
    for (int i = 0; i < 13; i++) { 
        if (i == 5) { // this if is impelemtneted to print the upper combinations total  with the respective combination
            printf(DIM"\t\t%2d. %-16s %3d " RESET,(i+1),com[i], AIScore[i]);
            printf(BOLD "%3d\n" RESET, AIn);
        } else if (i == 12) { // this if is impelemtneted to print the lower combinations total  with the respective combination
            printf(DIM"\t\t%2d. %-16s %3d " RESET,(i+1),com[i], AIScore[i]);
            printf(BOLD "%3d\n" RESET, AIo);   
        }else { // this if is impelemtneted to print the combinations that dont need print the score.
            printf(DIM"\t\t%2d. %-16s %3d \n" RESET,(i+1),com[i], AIScore[i]);    
        } 
    }
    printf(BOLD "\t\t    Current Total Score: %3d\n\n" RESET , AIo + AIn);
}



int main() {
    srand(time(0));// only call once. this will generate random numbers compared to the time in seconds. this will remove the squential random number ger=neration.

    char input;

    //defining the structures
    players user;
    players AI;

    instruct();//instructions to play
    playerName(user.name);// input the name of the player
    AIName(AI.name);// input the name of the AI
    important();//important information how the games should be played

    do {//loop that plays the game
        runningFun(user.dice, combinationNames, user.combinations, AI.combinations, &user.index, &user.uScore, &user.lScore, AI.dice, &AI.uScore, &AI.lScore, user.name, AI.name, user.scoredScore, AI.scoredScore);
        scoreDisplay(user.name, user.uScore, user.lScore, &user.total, 0);//display player's final Score
        scoreDisplay(AI.name, AI.uScore, AI.lScore, &AI.total, 1);//display AI's final Score
        winner(user.total, AI.total, user.name, AI.name);//choosing the winner
        printf("Do you want to play again?\n\tPress 'Y' to play again,\n\tPress 'N' to stop playing.\t");
        input = getchar();
        clearInputs();
        while (1) {
            if ((input == 'Y') || (input == 'N') || (input == 'y') || (input == 'n')) {
                break;
            } else {
                printf(RED"Invalid input either enter 'Y' or 'N' : "RESET);
                input = getchar();
                clearInputs();
            }
        }
    } while ((input == 'Y') || (input == 'y'));
    
    //statistics
    //statistics(combinationNames, AI.combinations,  AI.dice, &AI.uScore, &AI.lScore, AI.scoredScore);
  
    return 0;
}