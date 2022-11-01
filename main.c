// ECE 209 - Program 2: Farkle
// This program allows multiple users to play the dice game  Farkle.
// Rules of the game: https://www.dicegamedepot.com/farkle-rules/
// Number of players: 2 to 4
// Jason Robinson
//random number generator written by Dr. Greg Byrd at NC State

#include <stdio.h>
// DO NOT include or use any other standard library routines
// There is NO NEED to use strings in this program.
// NO GLOBAL VARIABLES

// functions and variables for random number generation
void seedRandom(unsigned int seed);  // initialize random number generator
unsigned int getRandom(unsigned int limit);  // returns random integer between 0 and limit-1

// dice data structure: an array of seven values
// index 0: total number of dice in the collection
// index 1-6: element i is the number of dice with face value = i
typedef int DiceGroup[7];
// if you don't understand how typedef works, or just prefer to not use this type,
// just declare an array of 7 integers instead -- you will not lose points for this

int takeTurn();   // interact with user to roll dice and return score
void rollDice(DiceGroup, int);     // initialize a specified number of dice
void printDice(const DiceGroup);   // print dice as a sorted sequence of digits
int selectDice(DiceGroup dice, DiceGroup keep, int choice);   // move dice from initial set to "keep" set
int scoreDice(const DiceGroup);    // return highest score available for a set of dice
int setDice(DiceGroup, int);       // initialize dice using an integer representation
int testFarkle(const DiceGroup);   // return 1 if no scoring dice
// You may declare additional functions here if they are defined below.

// DO NOT DEFINE functions above the main function -- you will lose points
// main function: user interface
int main() {
    int players = 0;  // number of players -- must be 2 to 4
    int scores[4] = {0};  // player scores -- start at zero
    int winner = 0;       // winning player (zero until someone wins)
    int p = 0;            // current player
    int i;        // used for loops
    unsigned int seed;    // initializer for random number generator

    setbuf(stdout, 0);
    printf("Welcome to Farkle!\nHow many players? ");
    scanf("%d", &players);
    if ((players < 1) || (players > 4)) {
        printf("This game only supports 1 to 4 players. How many? ");
        scanf("%d", &players);
    }
    printf("Enter a seed integer (decimal or hexadecimal): ");
    scanf("%i", &seed);
    seedRandom(seed);

    while (!winner) {
        int score = 0;
        printf("\nSCORES -- ");
        for (i = 0; i < players; i++) printf("%d: %d  ", i + 1, scores[i]);
        printf("\nPlayer %d's turn\n", p + 1);
        score = takeTurn();
        printf("Turn score = %d\n", score);
        if (players == 1) return 0;    // 1 player means one turn (used for testing)
        scores[p] += score;
        if (scores[p] >= 10000) winner = p + 1;
        p = (p + 1) % players;
    }
    printf("\nSCORES -- ");
    for (i = 0; i < players; i++) printf("%d: %d  ", i + 1, scores[i]);
    printf("\nPlayer %d wins!", winner);
    return 0;
}

// DEFINE your functions here -- above the PRNG code
void rollDice(DiceGroup dice, int n) {              //rolls dice to get pseudo random values using a seed
    int j = 1;
    int i;

    for (i = 0; i < 7; i++) {       //initialize used arrays to hold all zeroes
        dice[i] = 0;
    }


    dice[0] = n;
    int a = n;
    DiceGroup dicecheck;
    while (n > 0) {
        i = getRandom(6);

        dicecheck[j] = i + 1;

        j++;
        n--;
    }


    for (j = 1; j <= a; j++) {      //properly increments the dice array to be used as the dice data structure

        if (dicecheck[j] == 1) {
            dice[1]++;
        }
        if (dicecheck[j] == 2) {
            dice[2]++;
        }
        if (dicecheck[j] == 3) {
            dice[3]++;
        }
        if (dicecheck[j] == 4) {
            dice[4]++;
        }
        if (dicecheck[j] == 5) {
            dice[5]++;
        }
        if (dicecheck[j] == 6) {
            dice[6]++;
        }

    }
    return;
}


void printDice(const DiceGroup dice) {          //prints out the contents of a dice array
    int i = 0;
    int j = 1;
    for (j = 1; j < 7; j++) {
        i = dice[j];
        if (i > 0) {
            for (i = dice[j]; i > 0; i--) {
                printf("%d", j);
            }
        }
    }


    return;
}

int selectDice(DiceGroup dice, DiceGroup keep, int choice) {
    int a = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    DiceGroup save;


    a = choice;


    while (a != 0) {
        i++;
        a = a / 10;
    }

    for (k = 0; k < 7; k++) {              //copies original array to a safe array
        save[k] = dice[k];
    }


    for (i = i; i > 0; i--) {
        j = choice % 10;
        choice = choice / 10;
        if (j == 0 || j == 7 || j == 8 || j == 9) {
            for (k = 0; k < 7; k++) {                      //restores array to original contents in case function fails
                dice[k] = save[k];
            }


            return 0;
        }

        dice[j]--;
        if (dice[j] < 0) {

            for (k = 0; k < 7; k++) {                      //restores array to original contents in case function fails
                dice[k] = save[k];
            }


            return 0;
        }

        keep[j]++;
        dice[0]--;
        keep[0]++;

    }


    return 1;

}

int scoreDice(const DiceGroup dice) {       //returns proper score based off of what dice the player chooses to keep
    int x = 0;
    int j = 0;
    DiceGroup dicecheck;

    for (j = 1; j < 7; j++) {
        dicecheck[j] = dice[j];
    }
    if (dice[1] == 1 && dice[2] == 1 && dice[3] == 1 && dice[4] == 1 && dice[5] == 1 && dice[6] == 1) {
        return 1500;
    }
    if (dicecheck[6] == 6) {
        x = x + 1200;
        dicecheck[6] = dicecheck[6] - 6;
    }
    if (dicecheck[6] >= 3) {
        x = x + 600;
        dicecheck[6] = dicecheck[6] - 3;
    }
    if (dicecheck[5] == 6) {
        x = x + 1000;
        dicecheck[5] = dicecheck[5] - 6;
    }
    if (dicecheck[5] >= 3) {
        x = x + 500;
        dicecheck[5] = dicecheck[5] - 3;
    }
    if (dicecheck[4] == 6) {
        x = x + 800;
        dicecheck[4] = dicecheck[4] - 6;
    }
    if (dicecheck[4] >= 3) {
        x = x + 400;
        dicecheck[4] = dicecheck[4] - 3;
    }
    if (dicecheck[3] == 6) {
        x = x + 600;
        dicecheck[3] = dicecheck[3] - 6;
    }
    if (dicecheck[3] >= 3) {
        x = x + 300;
        dicecheck[3] = dicecheck[3] - 3;
    }
    if (dicecheck[2] == 6) {
        x = x + 400;
        dicecheck[2] = dicecheck[2] - 6;
    }
    if (dicecheck[2] >= 3) {
        x = x + 200;
        dicecheck[2] = dicecheck[2] - 3;
    }
    if (dicecheck[1] == 6) {
        x = x + 2000;
        dicecheck[1] = dicecheck[1] - 6;
    }
    if (dicecheck[1] >= 3) {
        x = x + 1000;
        dicecheck[1] = dicecheck[1] - 3;
    }
    if (dicecheck[5] < 3) {
        j = dicecheck[5];
        x = x + (j * 50);
    }
    if (dicecheck[1] < 3) {
        j = dicecheck[1];
        x = x + (j * 100);
    }
    return x;
}

int setDice(DiceGroup dice, int data) {             //allows the contents of the dice array to be set manually
    int i = 0;
    int j = 0;
    int a = 0;

    a = data;
    for (j = 0; j < 10; j++) {
        dice[j] = 0;
    }

    while (a != 0) {
        i++;
        a = a / 10;
    }
    dice[0] = i;

    for (j = 0; i > 0; i--) {
        j = data % 10;
        data = data / 10;

        if (j == 0 || j == 7 || j == 8 || j == 9) {
            return 0;
        } else {
            dice[j]++;
        }
    }

    return 1;
}

int testFarkle(const DiceGroup dice) {
    if (scoreDice(dice) == 0) {
        return 1;
    }
    return 0;
}

int takeTurn() {
    int n = 6;
    int score = 0;
    char check = 0;
    int choice = 0;
    DiceGroup dice;
    DiceGroup keep;
    DiceGroup save;
    int a = a;
    int i = 5;
    int k = 0;
    int c = 1;
    int selectdice = 0;
    int scoredice = 0;
    while (1) {
        while (1) {


            for (i = 0; i < 7; i++) {              //initializes contents of keep array to 0 each time
                keep[i] = 0;
            }

            rollDice(dice, n);
            for (k = 0; k < 7; k++) {              //copies original array to a safe array
                save[k] = dice[k];
            }
            printf("Rolling %d dice...", dice[0]);
            printDice(dice);
            printf("\n");
            if (testFarkle(dice) == 1) {
                printf("FARKLE -- your turn is over.\n");
                return 0;
            }
            printf("Which to keep? ");
            scanf("%d", &choice);


            selectdice = selectDice(dice, keep, choice);
            scoredice = scoreDice(keep);

            c = 0;
            while (selectdice == 0 || scoredice == 0) {         // checks for failed choice for scoring dice


                if (c != 0) {
                    selectdice = selectDice(dice, keep, choice);
                    c++;
                }


                if (selectdice == 0) {          //test 1
                    printf("No match, try again.\n");
                    printf("Which to keep? ");
                    for (k = 0;
                         k < 7; k++) {                      //restores array to original contents in case function fails
                        dice[k] = save[k];
                    }
                    for (k = 0; k < 7; k++) {
                        keep[k] = 0;
                    }
                    scanf("%d", &choice);
                    c++;
                    continue;
                }


                scoredice = scoreDice(keep);

                if (scoredice == 0) {      //test 2
                    printf("Must keep scoring dice. Try again.\n");
                    for (k = 0;
                         k < 7; k++) {                      //restores array to original contents in case function fails
                        dice[k] = save[k];
                    }
                    for (k = 0; k < 7; k++) {
                        keep[k] = 0;
                    }
                    printf("Which to keep? ");
                    scanf("%d", &choice);
                    c++;
                    continue;

                }

            }

            printf("Keeping ");
            printDice(keep);
            printf(", score = %d\n", scoreDice(keep));
            score = score + scoreDice(keep);
            printf("Score so far = %d\n", score);


            if (dice[0] == 0) {                     //checks for hot dice condition
                n = 6;
                printf("HOT DICE!  Roll 6 dice (y/n)? ");
                scanf(" %c", &check);

                if (check == 'n') {
                    return score;
                }
                n = 6;
                break;
            }
            if (dice[0] != 0) {                 //normal play route/non-hot dice
                printf("%d dice left -- roll again (y/n)? ", dice[0]);
                scanf(" %c", &check);
                if (check == 'n') {
                    return score;
                }

                n = dice[0];

            }


        }
    }


}

// DO NOT CHANGE or ADD any code below this line
//-------------------------------------------------------------------------------------------
// RANDOM NUMBER FUNCTIONS -- DO NOT CHANGE BELOW THIS LINE
// Using 16-bit linear feedback shift register (LFSR) for pseudorandom number generator
unsigned int lfsr = 0;  // global variable -- state of random number generator

// lfsrNext -- function to advance an LFSR for pseudorandom number generation
// uses global variable (lfsr)
// code from: https://en.wikipedia.org/wiki/Linear-feedback_shift_register
unsigned int lfsrNext(void) {
    lfsr ^= lfsr >> 7;
    lfsr ^= lfsr << 9;
    lfsr ^= lfsr >> 13;
    return lfsr;
}

// set starting value for LFSR-based random number generator
void seedRandom(unsigned int seed) {
    if (seed) lfsr = seed;
}

// return a random integer between 0 and limit-1
unsigned int getRandom(unsigned int limit) {
    return lfsrNext() % limit;  //
}
