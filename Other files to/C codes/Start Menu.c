#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main() {
    char username[50];
    int ans, game_ans, hangman_ans, mathalas_ans, nggame_ans;

    printf("Welcome. What do you like to be called?\n");
    scanf("%s", username);

    printf("\n\nHello, %s! What would you like to do?\n", username);

    do {
        printf("1. Play a game.\n2. Exit\nAnswer: ");
        scanf("%d", &ans);

        if (ans == 1) {
            printf("\nWhich game would you like to play?\n1. Hangman\n2. Math-alas\n3. Number Guessing Game\n4. Exit\nAnswer: ");
            scanf("%d", &game_ans);

            switch (game_ans) {
                case 1:
                    printf("\nWelcome to Hangman!\nDo you wish to proceed to the game?\n1. Yes.\n2. I'm kinda busy.\nAnswer: ");
                    scanf("%d", &hangman_ans);
                    switch (hangman_ans) {
                        case 1:
                            printf("\n\nProceeding to the game lobby...");
                            // hangman game block of codes
                            break;
                        case 2:
                            printf("\n\nCome again if you're ready to 'hang' 🙂.");
                            break;
                    }
                    break;
                case 2:
                    printf("\nWelcome to Math-alas!\nReady to kick number butts?\n1. I'm (in)!\n2. Nah, I'm out(.)\nAnswer: ");
                    scanf("%d", &mathalas_ans);
                    switch (mathalas_ans) {
                        case 1:
                            printf("\n\nPreparing the problems to be solved (inside the game, nothing personal)...");
                            // math-alas game block of codes
                            break;
                        case 2:
                            printf("\n\nGoodbye, potential math wizard. May you find solutions to your own problems.");
                            break;
                    }
                    break;
                case 3:
                    printf("\nWelcome to Number Guessing Game!\nAre you ready to guess?\n1. May the numeric prophecy unfold!\n2. I-I'm not quite s-sure about this...\nAnswer: ");
                    scanf("%d", &nggame_ans);
                    switch (nggame_ans) {
                        case 1:
                            printf("\n\nChoosing a number from 1 to 100...");
                            // number guessing game block of codes
                            break;
                        case 2:
                            printf("\n\nGoodbye.");
                            break;
                    }
                    break;
                case 4:
                    printf("\nThank you. Come again.");
                    break;
                default:
                    printf("\nInvalid input. Type a number from the options above.");
                    break;
            }
        } else if (ans == 2) {
            printf("\nVery well, User: %s! I hope you enjoyed your stay.", username);
        } else {
            printf("\nInvalid input. Please enter 1 to play a game or 2 to exit.");
        }
    } while (ans != 2); // Repeat until the user chooses to exit

    return 0;
}