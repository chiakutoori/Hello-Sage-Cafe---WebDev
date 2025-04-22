#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MAX_NUM 75

void generateCard(int card[SIZE][SIZE]) {
    int num;
    int used[MAX_NUM + 1] = {0}; // Array to track used numbers

    // Generate Bingo card
    for (int col = 0; col < SIZE; col++) {
        for (int row = 0; row < SIZE; row++) {
            do {
                if (col == 0) num = rand() % 15 + 1;           // B: 1-15
                else if (col == 1) num = rand() % 15 + 16;    // I: 16-30
                else if (col == 2) num = rand() % 15 + 31;    // N: 31-45
                else if (col == 3) num = rand() % 15 + 46;    // G: 46-60
                else num = rand() % 15 + 61;                   // O: 61-75
            } while (used[num]); // Ensure number is not repeated

            used[num] = 1; // Mark number as used
            card[row][col] = num;
        }
    }
    card[2][2] = 0; // Free space in the center
}

void printCard(int card[SIZE][SIZE]) {
    printf(" B   I   N   G   O\n");
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (card[row][col] == 0)
                printf(" *  "); // Mark free space
            else
                printf("%2d  ", card[row][col]);
        }
        printf("\n");
    }
}

void markCard(int card[SIZE][SIZE], int number) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (card[row][col] == number) {
                card[row][col] = 0; // Mark the number as 0
            }
        }
    }
}

int checkWin(int card[SIZE][SIZE]) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if ((card[i][0] == 0 && card[i][1] == 0 && card[i][2] == 0 &&
             card[i][3] == 0 && card[i][4] == 0) || // Check row
            (card[0][i] == 0 && card[1][i] == 0 && card[2][i] == 0 &&
             card[3][i] == 0 && card[4][i] == 0)) { // Check column
            return 1; // Win
        }
    }

    // Check diagonals
    if ((card[0][0] == 0 && card[1][1] == 0 && card[2][2] == 0 &&
         card[3][3] == 0 && card[4][4] == 0) || // Left to right diagonal
        (card[0][4] == 0 && card[1][3] == 0 && card[2][2] == 0 &&
         card[3][1] == 0 && card[4][0] == 0)) { // Right to left diagonal
        return 1; // Win
    }

    return 0; // No win
}

int main() {
    srand(time(NULL)); // Seed random number generator
    int card[SIZE][SIZE];
    int drawnNumber;
    int win = 0;

    generateCard(card);
    printCard(card);

    while (!win) {
        printf("Press Enter to draw a number...");
        getchar(); // Wait for user input

        drawnNumber = rand() % MAX_NUM + 1; // Draw a random number between 1 and 75
        printf("Drawn Number: %d\n", drawnNumber);
        markCard(card, drawnNumber);
        printCard(card);
        win = checkWin(card); // Check for a win condition

        if (win) {
            printf("Bingo! You've won!\n");
        }
    }

    return 0;
}