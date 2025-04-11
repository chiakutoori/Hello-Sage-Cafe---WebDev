#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()
#include <stdbool.h>

#define WIDTH 30
#define HEIGHT 10
#define GRAVITY 1
#define FLAP_STRENGTH 2
#define PIPE_WIDTH 3
#define PIPE_GAP_HEIGHT 4 // Height of the gap in the pipes
#define PIPE_LENGTH 8 // Length of the pipes

typedef struct {
    int x;
    int gap_start;
} Pipe;

typedef struct {
    int x;
    int y;
} Bird;

void draw(Bird bird, Pipe pipe) {
    system("cls"); // Clear the console

    // Draw the game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == bird.x && i == bird.y) {
                printf("B"); // Draw the bird
            } else if (j == pipe.x) {
                // Draw the upper part of the pipe
                if (i < pipe.gap_start || i >= pipe.gap_start + PIPE_GAP_HEIGHT) {
                    printf("#");
                } else {
                    printf(" ");
                }
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

bool check_collision(Bird bird, Pipe pipe) {
    return (bird.x == pipe.x && (bird.y < pipe.gap_start || bird.y >= pipe.gap_start + PIPE_GAP_HEIGHT));
}

void show_start_screen() {
    system("cls");
    printf("Welcome to Flappy Bird!\n");
    printf("Press any key to start...\n");
    _getch(); // Wait for user input
}

int main() {
    show_start_screen(); // Show the start screen

    Bird bird = {5, HEIGHT / 2}; // Start position of the bird
    Pipe pipe = {WIDTH - 1, 2}; // Start position of the pipe
    int velocity = 0; // Bird's vertical velocity
    bool game_over = false;

    while (!game_over) {
        // Draw the game state
        draw(bird, pipe);

        // Check for user input
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') { // Space bar to flap
                velocity = -FLAP_STRENGTH;
            }
        }

        // Update bird's position
        velocity += GRAVITY; // Apply gravity
        bird.y += velocity;

        // Move the pipe
        pipe.x--;

        // Reset pipe position and generate a new gap
        if (pipe.x < 0) {
            pipe.x = WIDTH - 1;
            pipe.gap_start = rand() % (HEIGHT - PIPE_GAP_HEIGHT - 1);
        }

        // Check for collisions
        if (bird.y < 0 || bird.y >= HEIGHT || check_collision(bird, pipe)) {
            game_over = true;
        }

        // Control the speed of the game
        Sleep(100);
    }

    printf("Game Over! Your bird hit a pipe or fell!\n");
    return 0;
}