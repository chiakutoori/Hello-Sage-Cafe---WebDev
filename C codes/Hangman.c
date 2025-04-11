#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 20
#define MAX_GUESSES 6

const char *word_list[MAX_WORDS] = {
    "programming",
    "hangman",
    "development",
    "computer",
    "science",
    "algorithm",
    "function",
    "variable",
    "pointer",
    "array"
};

// Function to display the hangman figure based on the number of incorrect guesses
void display_hangman(int incorrect_guesses) {
    switch (incorrect_guesses) {
        case 0:
            printf("  ----  \n");
            printf("  |    | \n");
            printf("       | \n");
            printf("       | \n");
            printf("       | \n");
            printf("       | \n");
            printf("=========\n");
            break;
        case 1:
            printf("  ----  \n");
            printf("  |    | \n");
            printf("  O    | \n");
            printf("       | \n");
            printf("       | \n");
            printf("       | \n");
            printf("=========\n");
            break;
        case 2:
            printf("  ----  \n");
            printf("  |    | \n");
            printf("  O    | \n");
            printf("  |    | \n");
            printf("       | \n");
            printf("       | \n");
            printf("=========\n");
            break;
        case 3:
            printf("  ----  \n");
            printf("  |    | \n");
            printf("  O    | \n");
            printf(" /|    | \n");
            printf("       | \n");
            printf("       | \n");
            printf("=========\n");
            break;
        case 4:
            printf("  ----  \n");
            printf("  |    | \n");
            printf("  O    | \n");
            printf(" /|\\   | \n");
            printf("       | \n");
            printf("       | \n");
            printf("=========\n");
            break;
        case 5:
            printf("  ----  \n");
            printf("  |    | \n");
            printf("  O    | \n");
            printf(" /|\\   | \n");
            printf(" /     | \n");
            printf("       | \n");
            printf("=========\n");
            break;
        case 6:
            printf("  ----  \n");
            printf("  |    | \n");
            printf("  O    | \n");
            printf(" /|\\   | \n");
            printf(" / \\   | \n");
            printf("       | \n");
            printf("=========\n");
            break;
    }
}

void init_game(const char **word, char *guessed_letters, char *incorrect_guesses) {
    // Randomly select a word from the list
    srand(time(NULL));
    *word = word_list[rand() % MAX_WORDS];
    
    // Initialize guessed letters and incorrect guesses
    memset(guessed_letters, '_', strlen(*word));
    guessed_letters[strlen(*word)] = '\0'; // Null-terminate the string
    incorrect_guesses[0] = '\0'; // Empty string for incorrect guesses
}

void display_game_state(const char *guessed_letters, const char *incorrect_guesses, int incorrect_count) {
    printf("Word: %s\n", guessed_letters);
    if (strlen(incorrect_guesses) > 0) {
        printf("Incorrect guesses: %s\n", incorrect_guesses);
    }
}

void make_guess(const char *word, char *guessed_letters, char *incorrect_guesses, char guess, int *num_guesses) {
    bool correct = false;
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == guess) {
            guessed_letters[i] = guess;
            correct = true;
        }
    }
    if (!correct) {
        // Check if the guess is already in incorrect guesses
        if (strchr(incorrect_guesses, guess) == NULL) {
            strncat(incorrect_guesses, &guess, 1);
            (*num_guesses)++;
        }
    }
}

bool check_win(const char *guessed_letters) {
    return strchr(guessed_letters, '_') == NULL; }

int main() {
    const char *word;
    char guessed_letters[MAX_WORD_LENGTH];
    char incorrect_guesses[MAX_WORDS]; // Store incorrect guesses
    int num_guesses = 0; // Count of incorrect guesses
    char guess;

    init_game(&word, guessed_letters, incorrect_guesses);

    while (num_guesses < MAX_GUESSES) {
        display_game_state(guessed_letters, incorrect_guesses, num_guesses);
        display_hangman(num_guesses); // Display the stickman figure

        printf("Enter your guess: ");
        scanf(" %c", &guess); // Read a character input

        // Convert guess to lowercase to handle case insensitivity
        guess = tolower(guess);

        // Validate input
        if (!isalpha(guess)) {
            printf("Please enter a valid letter.\n");
            continue;
        }

        // Make the guess
        make_guess(word, guessed_letters, incorrect_guesses, guess, &num_guesses);

        // Check for win condition
        if (check_win(guessed_letters)) {
            printf("Congratulations! You've guessed the word: %s\n", word);
            break;
        }
    }

    if (num_guesses == MAX_GUESSES) {
        display_hangman(num_guesses); // Show the final stickman
        printf("Game over! The word was: %s\n", word);
    }

    return 0;
}