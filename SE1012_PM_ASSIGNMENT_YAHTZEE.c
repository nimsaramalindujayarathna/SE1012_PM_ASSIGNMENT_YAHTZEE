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

void instruct();
int random_number();
void dice_readings(char *dices);
void diceRoll(char *dices);
void printDice(char *dices);

//combinations fucntions
int chance(char * dices);
int yahtzee(char *dices);
int largeStraight(char *dices);
int smallStraight(char *dices);
int fullHouse(char *dices);
int fourOfaKind(char *dices);
int threeOfaKind(char *dices);

//get input to choose which combination to choose
void userIndex(char *dices, int *combinationArray, int *combinationIndexNumber);

///output display fucntions
int bonus(int numbersScore);
void scoreDisplay(char *type, int nScore, int oScore, int *total);
void winner(int userFinal, int AIFinal);
void scoreForCombination(char *dices, int *combination, int *score);
void AIscoreForCombination(char *dices, int combinationNum, int *score);
void clearInputBuffer();

//final main function
void runningFun(char *dices,int *combinationArray,int combinationIndexNumber,int *combinationIndexNumberPointer, int *nScore, int *oScore, char *AIdices, int *AInScore, int *AIoScore);


int main() {
    srand(time(0));// only call once. this will generate random numbers compared to the time in seconds. this will remove the squential random number ger=neration.

    //variable Declaration

    //user scores
    char dices[5]; //dice readings
    int numbersScore= 0;
    int otherScore = 0;
    int finalScore = 0;

    //AI scores
    char AIDices[5]; //dice readings
    int AInumbersScore= 0;
    int AIotherScore = 0;
    int AIfinalScore = 0;

    //othere variables
    int checkNumber[] = {0, 0, 0, 0, 0, 0} ;
    // specialDice =0;

    //variables to store combinations selected
    int combinationsArray[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int combinationIndexNumber;
    int AICombinationsArray[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    //other variables
    char user[10] = "User's";
    char AI[12] = "Computer's";


    //instructions to play 
    instruct();

    //running Function
    runningFun(dices, combinationsArray, combinationIndexNumber, &combinationIndexNumber, &numbersScore, &otherScore, AIDices, &AInumbersScore, &AIotherScore);

    //display final Score
    scoreDisplay(user, numbersScore, otherScore, &finalScore);
    scoreDisplay(AI, AInumbersScore, AIotherScore, &AIfinalScore);
    
    //choosing the winner
    winner(finalScore, AIfinalScore);
    
    return 0;
}



//Displaying the Score
void scoreDisplay(char *type, int nScore, int oScore, int *total) {
    int tot;
    printf("\n%s Score.", type);
    printf("    Upper Combination Score : %d", nScore);
    printf("    Lower Combination Score : %d    ", oScore);
    printf("    Bonus Score : %d\n", bonus(nScore));
    tot = nScore + oScore + bonus(nScore);
    printf("%s Final Score : %d\n\n",type, tot);
    *total = tot;
}

//Choosing the winner
void winner(int userFinal, int AIFinal) {
    if(userFinal < AIFinal){
        printf("You tried your best buthe Ai is just Better.");
    } else if(userFinal > AIFinal) {
        printf("Congratulations, You have won the game");
    } else if(userFinal == AIFinal) {
        printf("IT'S a DRAW!!!");
    }
    printf("\n\n");
}

//bonus score
int bonus(int numbersScore){
if (numbersScore > 62){
        return 35;
    }
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
        printf("\n1 to 6:           Score based on the sum of the dice that show the chosen number.\n");
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

// this function will roll the dice 3 times and get the readings according to the user's preference and the array wich use to store the readings are pass as parameters
void diceRoll(char *dices) {
    char tempDices[5]; //tempary array to store temp dices
    int indexes; //indexs to keep
    int NoOfIndexes; // no of the indexes to keep
    int I; // varible used to print the rolll NO
    char inputChar; 
    printf("\nInital Dice Readings : ");
    dice_readings(dices); //Inital dice roll
    printDice(dices); //Inital deice reads displayed
    for (int i = 0; i < 2; i++) {
        printf("Do you want to roll the dices again? Press Yes - 'Y' or No - 'N' : ");
        scanf(" %c",&inputChar);
        // input validation ---- inputChar
        while(!(inputChar == 'Y' || inputChar == 'y' || inputChar == 'N' || inputChar == 'n')){
            printf("Invalid char input press either 'Y' or 'N'. Simple letters also works,\n");
            scanf(" %c",&inputChar);
        }
        if (inputChar == 'Y' || inputChar == 'y') {
            for (int j = 0; j < 5; j++ ) {
                tempDices[j] = dices[j]; //store the main array data to temp array to roll the dices again, while the values in the temp arrary are used to do the execution
            }
            dice_readings(dices); // next dice rolls. actually the programm roll the dice and store it in a array before asking the user what to do with the previous dice readings.
            printf("Enter how many dice readings you want to keep : "); 
            scanf("%d",&NoOfIndexes);
            //input validation ---- NoofIndexes
            while(!((NoOfIndexes >= 0) && (NoOfIndexes < 5))){
                printf("Invalid number of indexes. Please enter again. [0, 1, 2, 3, 4] : ");
                scanf("%d",&NoOfIndexes);
            }
            printf("Enter the number/s you want to keep for the next dice reading. (1 to 5)\n");
            for (int ii = 1; ii < NoOfIndexes + 1; ii++){
                printf("Enter the No %d dice reading. (1 to 5): ", ii );
                scanf("%d",&indexes);
                // input validation ---- indexes
                while(!((indexes > 0) && (indexes < 6))) {
                    printf("Invalid index enterd. Please enter again. (1 to 5) :");
                    scanf("%d",&indexes);
                }
                dices[indexes - 1] = tempDices[indexes - 1 ]; // the main array store the next roll data and occording to the indexes the values decided keep are assigned into the newly rolled main array
            }
            I = i + 2;
            printf("\nRoll NO (%d) : ",I); // this selection print the roll no
            printDice(dices); // print the new dices rolls
        } else if (inputChar == 'N' || inputChar == 'n') {
            break; // if the user do not want to roll again escape the function
        } 
    }
    printf("\nFinal Dice Readings are : ");
    printDice(dices); // after 3 dice rools or users's prefered dice rolls print  the dices
}



//chance function
int chance(char * dices){
    int sum = 0;
    for (int i = 0; i < 5;i++){
        sum = sum + dices[i];
    }
    return sum;
}

//yahtzee function
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

//large straight function
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

//small straight function
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

//full house function
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

//four of a kind function
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

//three of a kind function
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



//this function is used to get the user's combination for each dice rounds
void userIndex(char *dices, int *combinationArray, int *combinationIndexNumber){
    int index;
    char chars[13][20];
    snprintf(chars[0], 20, "Ones");
    snprintf(chars[1], 20, "Twos");
    snprintf(chars[2], 20, "Threes");
    snprintf(chars[3], 20, "Fours");
    snprintf(chars[4], 20, "Fives");
    snprintf(chars[5], 20, "Sixes");
    snprintf(chars[6], 20, "Three of a Kind");
    snprintf(chars[7], 20, "Four of a Kind");
    snprintf(chars[8], 20, "Full House");
    snprintf(chars[9], 20, "Small Straight");
    snprintf(chars[10], 20, "Large Straight");
    snprintf(chars[11], 20, "Chance");
    snprintf(chars[12], 20, "YAHTZEE");
    printf("\nCombinations Available to Choose.\n");
    // this prints the currently available combinations for user to choose from.
    for (int i = 0; i < 13; i++) { 
        if (combinationArray[i] == 0){
            printf("    %d. %s\n",(i+1),chars[i]);
        }
    }
    diceRoll(dices);
    //input validation for indexI variable
    while (1) {
        printf("Choose an available combination no (1 to 13): ");
        if (scanf("%d", &index) != 1) {  //check if the input is integer
            printf("Invalid input! Please enter a number between 1 and 13.\n");
            clearInputBuffer();  // Clear buffer if input is not a integer
            continue;
        }
        if (index < 1 || index > 13) { //for out of ranges inouts
            printf("Invalid input value. Please enter a number between 1 and 13.\n");
        } else if (combinationArray[index - 1] == 1) { // for prevoiously inutted value check
            printf("This combination has already been chosen! Please pick another.\n");
        } else {
            break;  // if the input is valid loop break
        }
    }
    combinationArray[index - 1] = 1;
    *combinationIndexNumber = index;
}

// this function will produce the score when the combination type is inputted
void scoreForCombination(char *dices, int *combinationNum, int *score){
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
    printf("Score for this round = %d\n",tempscore);
}

/// this function will produce the score when the combination type is inputted - for the AI
void AIscoreForCombination(char *dices, int combinationNum, int *score){
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
    printf("Score for this round = %d\n\n",tempscore);
}

//function that runs the 13 rounds
void runningFun(char *dices,int *combinationArray,int combinationIndexNumber,int *combinationIndexNumberPointer, int *nScore, int *oScore, char *AIdices, int *AInScore, int *AIoScore){
    int tempscore; // score for the respective condition
    int AItempscore; // score for the respective AI combination
    int sum1 = 0;
    int sum2 = 0;
    int AIsum1 = 0;
    int AIsum2 = 0;
    char chars[13][20];
    snprintf(chars[0], 20, "Ones");
    snprintf(chars[1], 20, "Twos");
    snprintf(chars[2], 20, "Threes");
    snprintf(chars[3], 20, "Fours");
    snprintf(chars[4], 20, "Fives");
    snprintf(chars[5], 20, "Sixes");
    snprintf(chars[6], 20, "Three of a Kind");
    snprintf(chars[7], 20, "Four of a Kind");
    snprintf(chars[8], 20, "Full House");
    snprintf(chars[9], 20, "Small Straight");
    snprintf(chars[10], 20, "Large Straight");
    snprintf(chars[11], 20, "Chance");
    snprintf(chars[12], 20, "YAHTZEE");
    for (int i = 0; i < 13; i++) {
        printf("\nRound No %d\n",i+1);                    
        printf("        YOUR MARKS     UPPER SECTION = %d  LOWER SECTION = %d   TOTAL SCORE = %d\n",sum1, sum2, sum1 + sum2 );
        printf("        AI MARKS       UPPER SECTION = %d  LOWER SECTION = %d   TOTAL SCORE = %d\n",AIsum1, AIsum2, AIsum1 + AIsum2 );
        userIndex(dices,combinationArray,combinationIndexNumberPointer);
        scoreForCombination(dices, combinationIndexNumberPointer, &tempscore);
        if (*combinationIndexNumberPointer < 7) {
            sum1 = sum1 + tempscore;
        } else {
            sum2 = sum2 + tempscore;
        }
        dice_readings(AIdices);
        printf("\nAI Dice Readings are : ");
        printDice(AIdices);
        printf("Combination Type : %s\n", chars[i]);
        AIscoreForCombination(AIdices, i + 1, &AItempscore);
        if (i+1 < 7) {
            AIsum1 = AIsum1 + AItempscore;
        } else {
            AIsum2 = AIsum2 + AItempscore;
        }
    }
    *nScore = sum1;
    *oScore = sum2;
    *AInScore = AIsum1;
    *AIoScore = AIsum2;
}



// this function is to get the inputs in the correct data type.
void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  // Discard invalid input and clear buffer
}


//define the respective AI's combination for each round respective to the user's
void AIIndex() {

}

