#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 10
#define HEIGHT 20

int field[HEIGHT][WIDTH] = {0}; // Game field
int score = 0;

// Tetromino shapes
int tetromino[7][4][4] = {
    {{1, 1, 1, 1}}, // I
    {{1, 1, 1}, {0, 1, 0}}, // T
    {{1, 1, 0}, {0, 1, 1}}, // S
    {{0, 1, 1}, {1, 1, 0}}, // Z
    {{1, 1}, {1, 1}}, // O
    {{1, 1, 1}, {1, 0, 0}}, // L
    {{1, 1, 1}, {0, 0, 1}}  // J
};

int currentTetromino[4][4]; // Current tetromino
int currentX, currentY; // Position of current tetromino
int currentType;

// Function prototypes
void initialize();
void draw();
void generateTetromino();
int collide(int offsetX, int offsetY);
void rotate();
void merge();
void clearLines();
void gameOver();

int main() {
    initialize();
    
    while (1) {
        draw();
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
                case 'a': // Move left
                    if (!collide(-1, 0)) currentX--;
                    break;
                case 'd': // Move right
                    if (!collide(1, 0)) currentX++;
                    break;
                case 's': // Move down
                    if (!collide(0, 1)) currentY++;
                    break;
                case 'w': // Rotate
                    rotate();
                    break;
                case 'q': // Quit
                    exit(0);
            }
        }

        // Move tetromino down
        if (!collide(0, 1)) {
            currentY++;
        } else {
            merge();
            clearLines();
            generateTetromino();
            if (collide(0, 0)) {
                gameOver();
                break;
            }
        }

        Sleep(100); // Control speed
    }

    return 0;
}

void initialize() {
    srand(time(NULL));
    generateTetromino();
}

void draw() {
    system("cls"); // Clear screen
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == 1) {
                printf("#"); // Draw filled block
            } else if (i >= currentY && i < currentY + 4 && j >= currentX && j < currentX + 4 && currentTetromino[i - currentY][j - currentX]) {
                printf("*"); // Draw current tetromino
            } else {
                printf(" "); // Draw empty space
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void generateTetromino() {
    currentType = rand() % 7; // Random tetromino
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            currentTetromino[i][j] = tetromino[currentType][i][j];

    currentX = WIDTH / 2 - 2; // Start position
    currentY = 0; // Start position
}

int collide(int offsetX, int offsetY) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentTetromino[i][j]) {
                int newX = currentX + j + offsetX;
                int newY = currentY + i + offsetY;
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && field[newY][newX ])) {
                    return 1; // Collision detected
                }
            }
        }
    }
    return 0; // No collision
}

void rotate() {
    int temp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[j][3 - i] = currentTetromino[i][j]; // Rotate 90 degrees

    // Check for collision after rotation
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (temp[i][j] && (currentX + j < 0 || currentX + j >= WIDTH || currentY + i >= HEIGHT || (currentY + i >= 0 && field[currentY + i][currentX + j]))) {
                return; // Collision, do not rotate
            }
        }
    }

    // Apply rotation
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            currentTetromino[i][j] = temp[i][j];
}

void merge() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentTetromino[i][j]) {
                field[currentY + i][currentX + j] = 1; // Merge tetromino into field
            }
        }
    }
}

void clearLines() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        int fullLine = 1;
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == 0) {
                fullLine = 0; // Line is not full
                break;
            }
        }
        if (fullLine) {
            score += 100; // Increase score
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < WIDTH; j++) {
                    field[k][j] = field[k - 1][j]; // Move lines down
                }
            }
            for (int j = 0; j < WIDTH; j++) {
                field[0][j] = 0; // Clear top line
            }
            i++; // Check the same line again
        }
    }
}

void gameOver() {
    system("cls");
    printf("Game Over! Your Score: %d\n", score);
    exit(0);
}