#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 15
#define MAX_ALIENS 5
#define MAX_BULLETS 10

typedef struct {
    int x;
    int y;
    int active; // 1 if bullet is active, 0 if not
} Bullet;

char board[HEIGHT][WIDTH];
int playerPos;
int alienPos[MAX_ALIENS];
int alienCount = MAX_ALIENS;
int gameOver = 0;
int score = 0;
Bullet bullets[MAX_BULLETS];

void initializeBoard() {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            board[i][j] = ' ';
    playerPos = WIDTH / 2;
    for (int i = 0; i < alienCount; i++) {
        alienPos[i] = i * 2; // Space aliens apart
    }
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0; // Initialize bullets as inactive
    }
}

void drawBoard() {
    system("cls"); // Clear the console
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == HEIGHT - 1 && j == playerPos) {
                printf("^"); // Player's spaceship
            } else {
                int isAlien = 0;
                for (int k = 0; k < alienCount; k++) {
                    if (i == 0 && j == alienPos[k]) {
                        printf("A"); // Alien
                        isAlien = 1;
                        break;
                    }
                }
                for (int b = 0; b < MAX_BULLETS; b++) {
                    if (bullets[b].active && bullets[b].x == j && bullets[b].y == i) {
                        printf("|"); // Bullet
                        isAlien = 1; // Prevent overwriting alien
                        break;
                    }
                }
                if (!isAlien) {
                    printf(" "); // Empty space
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void moveAliens() {
    static int direction = 1; // 1 for right, -1 for left
    for (int i = 0; i < alienCount; i++) {
        alienPos[i] += direction;
        if (alienPos[i] >= WIDTH - 1 || alienPos[i] <= 0) {
            direction *= -1; // Change direction
            for (int j = 0; j < alienCount; j++) {
                alienPos[j] += 1; // Move down
            }
            break;
        }
    }
    for (int i = 0; i < alienCount; i++) {
        if (alienPos[i] == playerPos && alienPos[i] >= HEIGHT - 1) {
            gameOver = 1; // Game over if an alien reaches the bottom
        }
    }
}

void shoot() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].x = playerPos;
            bullets[i].y = HEIGHT - 2; // Start just above the player's ship
            bullets[i].active = 1; // Mark bullet as active
            break;
        }
    }
}

void moveBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y--;
            if (bullets[i].y < 0) {
                bullets[i].active = 0; // Deactivate bullet if it goes off screen
            } else {
                for (int j = 0; j < alienCount; j++) {
                    if (bullets[i].y == 0 && bullets[i].x == alienPos[j]) {
                        bullets[i].active = 0; // Deactivate bullet
                        alienPos[j] = -1; // Remove the alien
                        score += 10; // Increase score
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    initializeBoard();
    while (!gameOver) {
        drawBoard();
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' && playerPos > 0) {
                playerPos--; // Move left
            } else if (ch == 'd' && playerPos < WIDTH - 1) {
                playerPos++; // Move right
            } else if (ch == ' ') {
                shoot(); // Shoot
            }
        }
        moveBullets();
        moveAliens();
        Sleep(200); // Control the speed of the game
    }
    printf("Game Over! Your score: %d\n", score);
    return 0;
}