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
void dice_readings(int *dice);
void printDice(int *diceArray);
void diceRoll(int *mainArray);
//int basicNumbers(int dicenumber, int *diceArray, int *check, int *number);
//void diceNumber(int*number);
int chance(int * dices);
int yahtzee(int *dices);
int largeStraight(int *dices);
int smallStraight(int *dices);
int fullHouse(int *dices);
int fourOfaKind(int *dices);
int threeOfaKind(int *dices);
void scoreTypeSelect(int *diceArray, int *nscore, int *oScore);
void combinationSelected(int *diceArray, int combination, int *sum);


int main(){
    srand(time(0)); // only call once. this will generate random numbers compared to the time in seconds. this will remove the squential random number ger=neration.
    
    int finalDiceReading[5]; // variable to store dice 5 readings
    int basicNumbersScoreSum = 0;
    int numbersScore= 0;
    int otherScore = 0;
    int finalScore = 0;
    int checkNumber[] = {0, 0, 0, 0, 0, 0} ;
    int specialDice =0;
    int bonusForNumbers = 0;
    
    scoreTypeSelect(finalDiceReading, &numbersScore, &otherScore);
    printf("Number Score : %d\n", numbersScore);
    printf("Other Score :%d\n", otherScore);
    if (numbersScore > 62){
        bonusForNumbers = 35;
    }
    finalScore = numbersScore + otherScore + bonusForNumbers;
    printf("Final Score : %d\n", finalScore);
}


// this function will generate random numbers from 1-6 getting the dice readings
int random_number(){
    return (rand() % 6) + 1;
} 


// this fuction will print the dice readings when the readings array is passed as an parameter
void printDice(int *diceArray){
    for (int i = 0; i < 5; i++){
        printf("%d ",diceArray[i]);
    }
    printf("\n");
}


// this function will generate 5 dice readings and store them in an array and the array name will be passed as an parameter
void dice_readings(int *dice) {
    for (int i = 0; i <=4; i++){
        dice[i] = random_number();
    }
}


// this function will roll the dice 3 times and get the readings according to the user's preference and the array wich use to store the readings are pass as parameters
void diceRoll(int *mainArray) {
    int tempArray[5]; //tempary array to store temp dices
    int indexes; //indexs to keep
    int NoOfIndexes; // no of the indexes to keep
    int I; // varible used to print the rolll NO
    char inputChar; 
    printf("\nInital Dice Readings : ");
    dice_readings(mainArray); //Inital dice roll
    printDice(mainArray); //Inital deice reads displayed
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
                tempArray[j] = mainArray[j]; //store the main array data to temp array to roll the dices again, while the values in the temp arrary are used to do the execution
            }
            dice_readings(mainArray); // next dice rolls. actually the programm roll the dice and store it in a array before asking the user what to do with the previous dice readings.
            printf("Enter how many dice readings you want to keep : "); 
            scanf("%d",&NoOfIndexes);
            //input validation ---- NoofIndexes
            while(!((NoOfIndexes >= 0) && (NoOfIndexes < 5))){
                printf("Invalid number of indexes. Please enter again. [0, 1, 2, 3, 4] : ");
                scanf("%d",&NoOfIndexes);
            }
            for (int ii = 0; ii < NoOfIndexes; ii++){
                printf("Enter the index you want to keep for the next dice reading. (0 to 4): ");
                scanf("%d",&indexes);
                // input validation ---- indexes
                while(!((indexes >= 0) && (indexes < 5))) {
                    printf("Invalid index enterd. Please enter again. (0 to 4) :");
                    scanf("%d",&indexes);
                }
                mainArray[indexes] = tempArray[indexes]; // the main array store the next roll data and occording to the indexes the values decided keep are assigned into the newly rolled main array
            }
            I = i + 2;
            printf("Roll NO : %d\n",I); // this selection print the roll no
            printDice(mainArray); // print the new dices rolls
        } else if (inputChar == 'N' || inputChar == 'n') {
            return; // if the user do not want to roll again escape the function
        } 
    }
    printf("Final Dice Readings are : ");
    printDice(mainArray); // after 3 dice rools or users's prefered dice rolls print  the dices
}

/*
// this fuction create the score for numbers value when the user chooses it.
int basicNumbers(int dicenumber, int *diceArray, int*check, int *number) {
    while(check[dicenumber - 1] == 1) {
        printf("You can not use the above entered value. Use these values : ");
        for (int i = 0; i < 6; i++) {
            if(check[i] == 0){
                int temp = i+1;
                printf("%d ",temp);
            }
        }
        printf("\n");
        diceNumber(number);
        dicenumber = *number;
    }
    check[dicenumber - 1] = 1;
    int sum =0;
    for (int i = 0; i < 5; i++){
        if (dicenumber == diceArray[i]){
            sum = sum + diceArray[i];
        }
    }
    return sum;
}


//this function will output the number which the user wants to assign the curent dice readings (only for numbers)
void diceNumber(int *number){
    int value ;
    printf("Value to Assign : ");
    scanf("%d",number);
    value = *number;
    while(!((value > 0) && (value < 7))) {
        printf("Invalid value. Please enter again. (1 to 6) :");
        scanf("%d",number);
        value = *number;
    }
}
*/

//chance function
int chance(int * dices){
    int sum = 0;
    for (int i = 0; i < 5;i++){
        sum = sum + dices[i];
    }
    return sum;
}

//yahtzee function
int yahtzee(int *dices){
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
int largeStraight(int *dices) {
    int array1[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        array1[dices[i] - 1]++ ;
    }
    if((array1[0] == 1 && array1[1] == 1 && array1[2] == 1 && array1[3] == 1 && array1[4] == 1) ||
       (array1[1] == 1 && array1[2] == 1 && array1[3] == 1 && array1[4] == 1 && array1[5] == 1)) {
        return 40;
    } else {
        return 0;
    }
}

//small straight function
int smallStraight(int *dices) {
    int array1[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        array1[dices[i] - 1]++ ;
    }
    if((array1[0] == 1 && array1[1] == 1 && array1[2] == 1 && array1[3] == 1) ||
       (array1[1] == 1 && array1[2] == 1 && array1[3] == 1 && array1[4] == 1) ||
       (array1[2] == 1 && array1[3] == 1 && array1[4] == 1 && array1[5] == 1)) {
        return 30;
    } else {
        return 0;
    }
}

//full house function
int fullHouse(int *dices){
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
int fourOfaKind(int *dices){
    int sum = 0;
    int array1[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5;i++){
        sum = sum + dices[i];
    }
    for (int ii = 0; ii < 5; ii++) {
        array1[dices[ii] - 1]++ ;
    }
    for (int j = 0; j < 6; j++) {
        if (array1[j] == 4){
            return sum;
        }
    }
    return 0;
}

//three of a kind function
int threeOfaKind(int *dices){
    int sum = 0;
    int array1[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5;i++){
        sum = sum + dices[i];
    }
    for (int ii = 0; ii < 5; ii++) {
        array1[dices[ii] - 1]++ ;
    }
    for (int j = 0; j < 6; j++) {
        if (array1[j] == 3){
            return sum;
        }
    }
    return 0;
}

//this function will promt the user to choose which combination that the user is willing to use for current dice readings
void scoreTypeSelect(int *diceArray, int *nScore, int *oScore){
    int array1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char chars[13][20];
    int indexI;
    int checknumb = 0;
    int tempscore = 0;
    int nnScore= 0;
    int ooScore = 0;
    snprintf(chars[0], 20, "Ones");
    snprintf(chars[1], 20, "Twos");
    snprintf(chars[2], 20, "Threes");
    snprintf(chars[3], 20, "Fours");
    snprintf(chars[4], 20, "Fives");
    snprintf(chars[5], 20, "Sixes");
    snprintf(chars[6], 20, "Three of a Kind");
    snprintf(chars[7], 20, "Fours of a Kind");
    snprintf(chars[8], 20, "Full House");
    snprintf(chars[9], 20, "Small Straight");
    snprintf(chars[10], 20, "Large Straight");
    snprintf(chars[11], 20, "Chance");
    snprintf(chars[12], 20, "YAHTZEE");
    for (int i = 0; i < 13; i++) {
        printf("\n\nRoll No %d                                          UPPER SECTION = %d  LOWER SECTION = %d\n",i + 1,nnScore,ooScore);
        printf("\nCombinations Available to Choose.\n");
        for (int ii = 0; ii < 13; ii++) { // this prints the currently available combinations for user to choose from.
            if (array1[ii] == 0){
                printf("    %d. %s\n",(ii+1),chars[ii]);
            }
        }
        diceRoll(diceArray);
        //input validation for indexI variable
        while (1){
            printf("Choose an available combination no (1 to 13): ");
            scanf("%d",&indexI);
            if (array1[indexI - 1] == 1) {  
                printf("This combination has already been chosen! Please pick another.\n");
                continue;
            } else if (indexI < 1 || indexI > 13){
                printf("Invalid input! Please enter a number between 1 and 13.\n");
                continue;
            } else {
                break;
            }
        }
        combinationSelected(diceArray, indexI, &tempscore);
        if (indexI < 7) {
            nnScore = nnScore + tempscore;
        } else {
            ooScore = ooScore + tempscore;
        }
        array1[indexI - 1] = 1;
    }
    *nScore = nnScore;
    *oScore = ooScore;
}


// this function choose which combination fucntions to run.
void combinationSelected(int *diceArray, int combination, int *sum){
    int score = 0;
    if (combination < 7){
        for (int i = 0; i < 5; i++) {
            if (diceArray[i] == combination) {
                score= score + diceArray[i];
            }
        }
    }
    else if(combination == 7) {
        score = threeOfaKind(diceArray);
    } else if(combination == 8) {
        score = fourOfaKind(diceArray);
    } else if(combination == 9) {
        score = fullHouse(diceArray);
    } else if(combination == 10) {
        score = smallStraight(diceArray);
    } else if(combination == 11) {
        score = largeStraight(diceArray);
    } else if(combination == 12) {
        score = chance(diceArray);
    }
    *sum = score;
}


