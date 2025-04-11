#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 20
#define MAX_GUESSES 6
#define MAX_NAME_LENGTH 50
#define MAX_MONSTERS 3

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

typedef struct {
    char name[MAX_NAME_LENGTH];
    int health;
    int attack;
    int level;
    int experience;
} Player;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int health;
    int attack;
} Monster;

void initialize_player(Player *player) {
    printf("Enter your character's name: ");
    fgets(player->name, MAX_NAME_LENGTH, stdin);
    player->name[strcspn(player->name, "\n")] = 0; // Remove newline character
    player->health = 100;
    player->attack = 10;
    player->level = 1;
    player->experience = 0;
}

void initialize_monsters(Monster monsters[]) {
    strcpy(monsters[0].name, "Goblin");
    monsters[0].health = 30;
    monsters[0].attack = 5;

    strcpy(monsters[1].name, "Orc");
    monsters[1].health = 50;
    monsters[1].attack = 10;

    strcpy(monsters[2].name, "Dragon");
    monsters[2].health = 100;
    monsters[2].attack = 20;
}

void display_status(Player player) {
    printf("\n--- Player Status ---\n");
    printf("Name: %s\n", player.name);
    printf("Health: %d\n", player.health);
    printf("Attack: %d\n", player.attack);
    printf("Level: %d\n", player.level);
    printf("Experience: %d\n", player.experience);
    printf("----------------------\n");
}

void battle(Player *player, Monster *monster) {
    printf("\nA wild %s appears!\n", monster->name);
    while (player->health > 0 && monster->health > 0) {
        // Player attacks monster
        monster->health -= player->attack;
        printf("%s attacks %s for %d damage!\n", player->name, monster->name, player->attack);
        printf("%s's health: %d\n", monster->name, monster->health);

        if (monster->health <= 0) {
            printf("%s defeated the %s!\n", player->name, monster->name);
            player->experience += 20;
            printf("You gained 20 experience points!\n");
            return;
        }

        // Monster attacks player
        player->health -= monster->attack;
        printf("%s attacks %s for %d damage!\n", monster->name, player->name, monster->attack);
        printf("%s's health: %d\n", player->name, player->health);
    }

    if (player->health <= 0) {
        printf("%s has been defeated!\n", player->name);
    }
}

void level_up(Player *player) {
    if (player->experience >= 100) {
        player->level++;
        player->experience -= 100;
        player->health += 20; // Increase health on level up
        player->attack += 5;   // Increase attack on level up
        printf("%s leveled up to level %d!\n", player->name, player->level);
        printf("Health increased to %d and attack increased to %d!\n", player->health, player->attack);
    }
}

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
    srand(time(NULL));
    *word = word_list[rand() % MAX_WORDS];
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
        if (strchr(incorrect_guesses, guess) == NULL) {
            strncat(incorrect_guesses, &guess, 1);
            (*num_guesses)++;
        }
    }
}

void play_hangman() {
    const char *word;
    char guessed_letters[MAX_WORD_LENGTH + 1];
    char incorrect_guesses[MAX_GUESSES + 1];
    int incorrect_count = 0;

    init_game(&word, guessed_letters, incorrect_guesses);

    while (incorrect_count < MAX_GUESSES && strcmp(guessed_letters, word) != 0) {
        display_hangman(incorrect_count);
        display_game_state(guessed_letters, incorrect_guesses, incorrect_count);

        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess); // Convert to lowercase for consistency

        make_guess(word, guessed_letters, incorrect_guesses, guess, &incorrect_count);
    }

    if (strcmp(guessed_letters, word) == 0) {
        printf("Congratulations! You've guessed the word: %s\n", word);
    } else {
        display_hangman(incorrect_count);
        printf("Game over! The word was: %s\n", word);
    }
}

void play_rpg() {
    Player player;
    Monster monsters[MAX_MONSTERS];
    int choice;

    srand(time(NULL)); // Seed for random number generation

    initialize_player(&player);
    initialize_monsters(monsters);

    do {
        display_status(player);
        printf("Choose an action:\n");
        printf("1. Explore the dungeon\n");
        printf("2. Exit the game\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        if (choice == 1) {
            int monster_index = rand() % MAX_MONSTERS; // Randomly select a monster
            battle(&player, &monsters[monster_index]);
            level_up(&player);
        }
 } while (choice != 2);

    printf("Thank you for playing, %s!\n", player.name);
}

int main() {
    int choice;

    do {
        printf("Welcome to the Game Menu!\n");
        printf("1. Play Hangman\n");
        printf("2. Play Text-Based RPG\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                play_hangman();
                break;
            case 2:
                play_rpg();
                break;
            case 3:
                printf("Exiting the game. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}