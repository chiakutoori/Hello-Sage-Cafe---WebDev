#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// G14 PROPERTY
#define WIDTH 40
#define HEIGHT 20
#define PACMAN 'C'
#define WALL '#'
#define FOOD '.'
#define EMPTY ' '
#define DEMON 'X'

// Placeholder for Math-alas game
void play_math_alas() {
    int num1, num2, answer, user_answer;
    char operator;
    int score = 0;
    int rounds = 10; // Number of rounds

    printf("Welcome to the Math-alas game!\n");

    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < rounds; i++) {
        num1 = rand() % 100; // Random number between 0 and 99
        num2 = rand() % 100; // Random number between 0 and 99
        operator = (rand() % 2) ? '+' : '-'; // Randomly choose + or -

        // Calculate the correct answer
        if (operator == '+') {
            answer = num1 + num2;
        } else {
            answer = num1 - num2;
        }

        // Ask the user for their answer
        printf("Round %d: What is %d %c %d? ", i + 1, num1, operator, num2);
        scanf("%d", &user_answer);

        // Check if the answer is correct
        if (user_answer == answer) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect! The correct answer was %d.\n", answer);
        }
    }

    printf("Game over! Your score: %d out of %d\n", score, rounds);
}

// Pac-Man game functions
int res = 0; 
int score = 0; 
int pacman_x, pacman_y; 
char board[HEIGHT][WIDTH]; 
int food = 0; 
int curr = 0; 

void initialize() {
    srand(time(NULL));

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1) {
                board[i][j] = WALL;
            } else {
                board[i][j] = EMPTY;
            }
        }
    }

    int count = 50;
    while (count > 0) {
        int i = rand() % (HEIGHT - 2) + 1; // Avoid walls
        int j = rand() % (WIDTH - 2) + 1;  // Avoid walls

        if (board[i][j] != WALL && board[i][j] != PACMAN) {
            board[i][j] = WALL;
            count--;
        }
    }

    int demonCount = 5; // Start with 5 demons
    while (demonCount > 0) {
        int i = rand() % (HEIGHT - 2) + 1;
        int j = rand() % (WIDTH - 2) + 1;

        if (board[i][j] != WALL && board[i][j] != PACMAN) {
            board[i][j] = DEMON;
            demonCount--;
        }
    }

    pacman_x = WIDTH / 2;
    pacman_y = HEIGHT / 2;
    board[pacman_y][pacman_x] = PACMAN;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i % 2 == 0 && j % 2 == 0 && board[i][j] == EMPTY) {
                board[i][j] = FOOD;
                food++;
            }
        }
    }

    while (food < 50) {
        int i = rand() % (HEIGHT - 2) + 1;
        int j = rand() % (WIDTH - 2) + 1;

        if (board[i][j] == EMPTY) {
            board[i][j] = FOOD;
            food++;
        }
    }
}

void draw() {
    system("cls"); // Clear screen
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void move(int move_x, int move_y) {
    int x = pacman_x + move_x;
    int y = pacman_y + move_y;

    if (board[y][x] != WALL) {
        if (board[y][x] == FOOD) {
            score++;
            food--;
            curr++;
            if (score >= 50) { // Win condition changed to require a score of 50
                res = 2; // Win condition
                return;
            }
        } else if (board[y][x] == DEMON) {
            res = 1; // Lose condition
        }

        board[pacman_y][pacman_x] = EMPTY;
        pacman_x = x;
        pacman_y = y;
        board[pacman_y][pacman_x] = PACMAN;
    }
}

void moveDemons() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == DEMON) {
                int move_x = (rand() % 3) - 1; // Randomly move left, right, or stay
                int move_y = (rand() % 3) - 1; // Randomly move up, down, or stay
                int new_x = j + move_x;
                int new_y = i + move_y;

                // Check boundaries and walls
                if (new_x > 0 && new_x < WIDTH - 1 && new_y > 0 && new_y < HEIGHT - 1 && board[new_y][new_x] != WALL) {
                    // Move demon to new position
                    board[i][j] = EMPTY; // Clear old position
                    board[new_y][new_x] = DEMON; // Set new position
                }
            }
        }
    }
}

void play_pacman() {
    initialize();
    char ch;
    food -= 35; // Adjust food count
    int totalFood = food;

    printf("Use buttons for w(up), a(left), d(right), and s(down)\nPress q to quit\n");
    printf("Enter Y to continue: \n");

    ch = getch();
    if (ch != 'Y' && ch != 'y') {
        printf("Exit Game! ");
        return;
    }

    while (1) {
        draw();
        moveDemons(); // Move demons after drawing

        printf("Total Food count: %d\n", totalFood);
        printf("Total Food eaten: %d\n", curr);

        if (res == 1) {
            system("cls");
            printf("Game Over! Dead by Demon\nYour Score: %d\n", score);
            return;
        }

        if (res == 2) {
            system("cls");
            printf("You Win! \nYour Score: %d\n", score);
            return;
        }

        ch = getch(); // Taking input from the user

        switch (ch) {
        case 'w':
            move(0, -1);
            break;
        case 's':
            move(0, 1);
            break;
        case 'a':
            move(-1, 0);
            break;
        case 'd':
            move(1, 0);
            break;
        case 'q':
            printf("Game Over! Your Score: %d\n", score);
            return;
        }
    }
}

// Snake and Ladder Game Functions
int rollDie() { return rand() % 6 + 1; }

int player1 = 0, player2 = 0;

void printBoard() {
    int board[101];
    for (int i = 1; i <= 100; i++) {
        board[i] = i;
    }

    int alt = 0; // to switch between the alternate nature of the board
    int iterLR = 101; // iterator to print from left to right
    int iterRL = 80;  // iterator to print from right to left
    int val = 100;
    while (val--) {
        if (alt == 0) {
            iterLR--;
            if (iterLR == player1) {
                printf("#P1    ");
            } else if (iterLR == player2) {
                printf("#P2    ");
            } else {
                printf("%d    ", board[iterLR]);
            }

            if (iterLR % 10 == 1) {
                printf("\n\n");
                alt = 1;
                iterLR -= 10;
            }
        } else {
            iterRL++;
            if (iterRL == player1) {
                printf("#P1    ");
            } else if (iterRL == player2) {
                printf("#P2    ");
            } else {
                printf("%d    ", board[iterRL]);
            }

            if (iterRL % 10 == 0) {
                printf("\n\n");
                alt = 0;
                iterRL -= 30;
            }
        }
        if (iterRL == 10)
            break;
    }
    printf("\n");
}

int movePlayer(int currentPlayer, int roll) {
    int newPosition = currentPlayer + roll;
    int snakesAndLadders[101];

    for (int i = 0; i <= 100; i++) {
        snakesAndLadders[i] = 0;
    }

    snakesAndLadders[6] = 40;
    snakesAndLadders[23] = -10;
    snakesAndLadders[45] = -7;
    snakesAndLadders[61] = -18;
    snakesAndLadders[65] = -8;
    snakesAndLadders[77] = 5;
    snakesAndLadders[98] = -10;

    int newSquare = newPosition + snakesAndLadders[newPosition];

    if (newSquare > 100) {
        return currentPlayer; // Player cannot move beyond square 100
    }

    return newSquare;
}

void play_snake_ladders() {
    srand(time(0)); // Initialize random seed
    int currentPlayer = 1;
    int won = 0;

    printf("Snake and Ladder Game\n");

    while (!won) {
        printf("\nPlayer %d, press Enter to roll the die...", currentPlayer);
        getchar(); // Wait for the player to press Enter
        int roll = rollDie();
        printf("You rolled a %d.\n", roll);

        if (currentPlayer == 1) {
            player1 = movePlayer(player1, roll);
            printf("Player 1 is now at square %d.\n\n", player1);
            printBoard();
            if (player1 == 100) {
                printf("Player 1 wins!\n");
                won = 1;
            }
        } else {
            player2 = movePlayer(player2, roll);
            printf("Player 2 is now at square %d.\n\n", player2);
            printBoard();
            if (player2 == 100) {
                printf("Player 2 wins!\n");
                won = 1;
            }
        }

        // Switch to the other player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

// Main menu code
int main() {
    char username[50];
    int ans;

    printf("Welcome user. What do you like to be called?\n");
    scanf("%s", username);

    printf("\n\nHello, %s! What would you like to do?\n", username);

    do {
        printf("1. Play Math-alas.\n2. Play Pac-Man.\n3. Play Snake and Ladders.\n4. Exit\nAnswer: ");
        scanf("%d", &ans);

        if (ans == 1) {
            printf("\nWelcome to Math-alas!\n");
            play_math_alas(); // Call the Math-alas game function
        } else if (ans == 2) {
            printf("\nWelcome to Pac-Man!\n");
            play_pacman(); // Call the Pac-Man game function
        } else if (ans == 3) {
            printf("\nWelcome to Snake and Ladders!\n");
            play_snake_ladders(); // Call the Snake and Ladders game function
        } else if (ans == 4) {
            printf("\nVery well, User: %s! I hope you enjoyed your stay.\n", username);
        } else {
            printf("\nInvalid input. Please enter 1 to play Math-alas, 2 to play Pac-Man, 3 to play Snake and Ladders, or 4 to exit.\n");
        }
    } while (ans != 4); // Repeat until the user chooses to exit

    return 0;
}