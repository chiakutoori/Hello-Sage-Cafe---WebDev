#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUESTIONS 5

int generateRandomOperator() {
    // Gnenerates a random operator: +. -, or *
    return rand() % 3; // 0 for +, 1 for -, 2 for *
}

int calculateAnswer(int num1, int num2, int operator) {
    switch (operator) {
        case 0: return num1 + num2;
        case 1: return num1 - num2;
        case 2: return num1 * num2;
        default: return 0;
    }
}

void playGame() {
    int score = 0;
    int consecutiveCorrect = 0;
    int num1, num2, operator, userAnswer, correctAnswer;

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        num1 = rand() % 10 + 1;
        num2 = rand() % 10 + 1;
        operator = generateRandomOperator();
        correctAnswer = calculateAnswer(num1, num2, operator);

        // Display the question
        printf("Question %d: %d ", i + 1, num1);
        switch (operator) {
            case 0: printf("+"); break;
            case 1: printf("-"); break;
            case 2: printf("*"); break;        
        }
        printf(" %d = ?\n", num2);

        // get user's answer
        printf("Your answer: ");
        scanf("%d", &userAnswer);

        //check the answer
        if (userAnswer == correctAnswer) {
            consecutiveCorrect++;
            score += 10 + (consecutiveCorrect * 5);
            printf("Correct! Your score: %d\n", score);
        } else {
            consecutiveCorrect = 0;
            score = 0;
            printf("Incorrect! The correct answer was %d. Your score: %d\n", correctAnswer, score);           
        }
    }

    printf("Game over! Your final score: %d\n", score);
}

int main() {
    srand(time(0));
    printf("Welcome to the Math Game!\n");
    playGame();
    return 0;
}