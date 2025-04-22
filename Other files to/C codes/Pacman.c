#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20
#define PACMAN 'C'
#define WALL '#'
#define FOOD '.'
#define EMPTY ' '
#define DEMON 'X'

int res = 0; 
int score = 0; 
int pacman_x, pacman_y; 
char board[HEIGHT][WIDTH]; 
int food = 0; 
int curr = 0; 

void initialize() {
    // Initialize random seed
    srand(time(NULL));

    // Put walls as boundaries in the game
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1) {
                board[i][j] = WALL;
            } else {
                board[i][j] = EMPTY;
            }
        }
    }

    // Place walls inside the game
    int count = 50;
    while (count > 0) {
        int i = rand() % (HEIGHT - 2) + 1; // Avoid walls
        int j = rand() % (WIDTH - 2) + 1;  // Avoid walls

        if (board[i][j] != WALL && board[i][j] != PACMAN) {
            board[i][j] = WALL;
            count--;
        }
    }

    // Place enemies in the game (X symbols) 
    int demonCount = 5; // Start with 5 enemies
    while (demonCount > 0) {
        int i = rand() % (HEIGHT - 2) + 1;
        int j = rand() % (WIDTH - 2) + 1;

        if (board[i][j] != WALL && board[i][j] != PACMAN) {
            board[i][j] = DEMON;
            demonCount--;
        }
    }

    // Place Pac-Man at the center
    pacman_x = WIDTH / 2;
    pacman_y = HEIGHT / 2;
    board[pacman_y][pacman_x] = PACMAN;

    // Place food - Increase the amount of food
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i % 2 == 0 && j % 2 == 0 && board[i][j] == EMPTY) {
                board[i][j] = FOOD;
                food++;
            }
        }
    }

    // Ensure at least 50 food items are placed
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
    for (int i = 0 ; i < HEIGHT; i++) {
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

int main() {
    initialize();
    char ch;
    food -= 35; // Adjust food count
    int totalFood = food;

    printf("Use buttons for w(up), a(left), d(right), and s(down)\nPress q to quit\n");
    printf("Enter Y to continue: \n");

    ch = getch();
    if (ch != 'Y' && ch != 'y') {
        printf("Exit Game! ");
        return 1;
    }

    while (1) {
        draw();
        moveDemons(); // Move demons after drawing

        printf("Total Food count: %d\n", totalFood);
        printf("Total Food eaten: %d\n", curr);

        if (res == 1) {
            system("cls");
            printf("Game Over! Dead by Demon\nYour Score: %d\n", score);
            return 1;
        }

        if (res == 2) {
            system("cls");
            printf("You Win! \nYour Score: %d\n", score);
            return 1;
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
            return 0;
        }
    }

    return 0;
}