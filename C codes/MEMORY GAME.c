#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 4
#define MAX_WORD_LENGTH 20
#define MAX_WORDS 100

char grid[SIZE][SIZE]; // The letter grid
char valid_words[MAX_WORDS][MAX_WORD_LENGTH] = {
    "CAT", "DOG", "BIRD", "FISH", "COW", "HORSE", "RAT", "BAT", "ANT", "BEAR"
}; // Predefined valid words
int word_count = 10; // Number of valid words

// Function to initialize the grid with random letters
void initialize_grid() {
    const char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = letters[rand() % strlen(letters)];
        }
    }
}

// Function to display the grid
void display_grid() {
    printf("Current Grid:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a word is valid
int is_valid_word(const char *word) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(valid_words[i], word) == 0) {
            return 1; // Word is valid
        }
    }
    return 0; // Word is not valid
}

// Function to get the word from the user based on coordinates
void get_word_from_coordinates(char *word) {
    int length = 0;
    int x, y;

    printf("Enter the coordinates of the letters (row column) or -1 -1 to finish:\n");
    while (1) {
        printf("Enter coordinates: ");
        scanf("%d %d", &x, &y);
        if (x == -1 && y == -1) {
            break; // Exit condition
        }
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            printf("Invalid coordinates! Try again.\n");
            continue;
        }
        word[length++] = grid[x][y]; // Add letter to word
        word[length] = '\0'; // Null-terminate the string
    }
}

// Main game function
void play_bookworm() {
    char word[MAX_WORD_LENGTH];
    int score = 0;

    initialize_grid();
    display_grid();

    while (1) {
        get_word_from_coordinates(word);
        if (strlen(word) == 0) {
            break; // Exit if no word entered
        }
        if (is_valid_word(word)) {
            printf("Valid word: %s\n", word);
            score += strlen(word); // Increment score by word length
        } else {
            printf("Invalid word: %s\n", word);
        }
    }

    printf("Game over! Your score: %d\n", score);
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    play_bookworm(); // Start the game
    return 0;
}