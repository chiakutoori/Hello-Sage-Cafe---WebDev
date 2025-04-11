#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()

#define WIDTH 40
#define HEIGHT 20
#define PADDLE_HEIGHT 4
#define BALL_SPEED 1

typedef struct {
    int x, y;
} Ball;

typedef struct {
    int x, y;
} Paddle;

void draw(Ball ball, Paddle leftPaddle, Paddle rightPaddle, int leftScore, int rightScore) {
    system("cls"); // Clear the console

    // Draw the top border
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    // Draw the game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                printf("#"); // Left border
            }

            if (j == ball.x && i == ball.y) {
                printf("O"); // Draw the ball
            } else if (j == leftPaddle.x && i >= leftPaddle.y && i < leftPaddle.y + PADDLE_HEIGHT) {
                printf("|"); // Draw the left paddle
            } else if (j == WIDTH - 1 && i >= rightPaddle.y && i < rightPaddle.y + PADDLE_HEIGHT) {
                printf("|"); // Draw the right paddle
            } else {
                printf(" ");
            }

            if (j == WIDTH - 1) {
                printf("#"); // Right border
            }
        }
        printf("\n");
    }

    // Draw the bottom border
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    // Draw the scores
    printf("Score: Player 1: %d | Player 2: %d\n", leftScore, rightScore);
}

int main() {
    Ball ball = {WIDTH / 2, HEIGHT / 2};
    Paddle leftPaddle = {0, (HEIGHT - PADDLE_HEIGHT) / 2};
    Paddle rightPaddle = {WIDTH - 1, (HEIGHT - PADDLE_HEIGHT) / 2};

    int leftScore = 0, rightScore = 0;
    int ballVelocityX = BALL_SPEED, ballVelocityY = BALL_SPEED;

    while (1) {
        // Draw the game state
        draw(ball, leftPaddle, rightPaddle, leftScore, rightScore);

        // Move the ball
        ball.x += ballVelocityX;
        ball.y += ballVelocityY;

        // Ball collision with top and bottom
        if (ball.y <= 0 || ball.y >= HEIGHT - 1) {
            ballVelocityY = -ballVelocityY; // Reverse direction
        }

        // Ball collision with paddles
        if ((ball.x == leftPaddle.x + 1 && ball.y >= leftPaddle.y && ball.y < leftPaddle.y + PADDLE_HEIGHT) ||
            (ball.x == rightPaddle.x - 1 && ball.y >= rightPaddle.y && ball.y < rightPaddle.y + PADDLE_HEIGHT)) {
            ballVelocityX = -ballVelocityX; // Reverse direction
        }

        // Scoring
        if (ball.x < 0) {
            rightScore++;
            ball.x = WIDTH / 2; // Reset ball position
            ball.y = HEIGHT / 2;
            ballVelocityX = BALL_SPEED; // Reset ball speed
        } else if (ball.x >= WIDTH) {
            leftScore++;
            ball.x = WIDTH / 2; // Reset ball position
            ball.y = HEIGHT / 2;
            ballVelocityX = -BALL_SPEED; // Reset ball speed
        }

        // Paddle movement
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'w' && leftPaddle.y > 0) {
                leftPaddle.y--; // Move left paddle up
            } else if (ch == 's' && leftPaddle.y < HEIGHT - PADDLE_HEIGHT) {
                leftPaddle.y++; // Move left paddle down
            } else if (ch == 72 && rightPaddle.y > 0) { // Up arrow key
 rightPaddle.y--; // Move right paddle up
            } else if (ch == 80 && rightPaddle.y < HEIGHT - PADDLE_HEIGHT) { // Down arrow key
                rightPaddle.y++; // Move right paddle down
            }
        }

        Sleep(100); // Control the game speed
    }

    return 0;
}