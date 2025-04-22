#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess, attempts = 0;
    const int MAX_NUMBER = 100;
    int hintRequested = 0;

    // Seed the random number generator
    srand(time(NULL));
    number = rand() % MAX_NUMBER + 1; // Generate a random number between 1 and 100

    printf("Welcome to the Number Guessing Game!\n");
    printf("I have selected a number between 1 and %d. Can you guess it?\n", MAX_NUMBER);

    // Game loop
    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess < number) {
            printf("Too low! Try again.\n");
        } else if (guess > number) {
            printf("Too high! Try again.\n");
        }

        // Check if the player has made more than 5 incorrect attempts
        if (attempts > 5 && !hintRequested) {
            int choice;
            printf("You've made more than 5 incorrect attempts. Do you want a hint? (1 for yes, 2 for no): ");
            scanf("%d", &choice);

            if (choice == 1) {
                hintRequested = 1;
                // Provide a hint based on the correct number
                int lowerBound = (number > 5) ? number - 5 : 1;
                int upperBound = (number < MAX_NUMBER - 5) ? number + 5 : MAX_NUMBER;
                printf("Here's a hint: The number is between %d and %d.\n", lowerBound, upperBound);

            } else if (choice == 2) {
                printf("No hint for you! Good luck, challenger!\n");
            } else {
                printf("Invalid choice. No hint for you! keep trying.\n");
            }
        } 

    } while (guess != number);

    printf("Congratulaions! You've guessed the number %d in %d attempts!\n", number, attempts);

    return 0;
} 