#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to get a random integer between min and max (inclusive)
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to get a random operator
char getRandomOperator() {
    char operators[] = {'+', '-', '*', '/'};
    return operators[rand() % 4];
}

int main() {
    // Seed the random number generator
    srand(time(NULL));
    
    // Generate 5 random numbers
    int numbers[5];
    for (int i = 0; i < 5; i++) {
        numbers[i] = getRandomNumber(1, 20);
    }
    
    // Generate 4 random operators
    char operators[4];
    for (int i = 0; i < 4; i++) {
        operators[i] = getRandomOperator();
    }
    
    // Print the math expression
    printf("Solve this expression using MDAS (Multiplication, Division, Addition, Subtraction) rule:\n");
    
    // Print the first number
    printf("%d ", numbers[0]);
    
    // Print the rest of the numbers and operators
    for (int i = 0; i < 4; i++) {
        printf("%c %d ", operators[i], numbers[i+1]);
    }
    
    printf("\n\nEnter your answer: ");
    
    // Variable to store user's answer
    double userAnswer;
    scanf("%lf", &userAnswer);
    
    // Calculate the actual answer
    double result = numbers[0];
    
    // First pass: Multiplication and Division
    for (int i = 0; i < 4; i++) {
        if (operators[i] == '*' || operators[i] == '/') {
            switch(operators[i]) {
                case '*':
                    result *= numbers[i+1];
                    break;
                case '/':
                    if (numbers[i+1] != 0) {  // Prevent division by zero
                        result /= numbers[i+1];
                    } else {
                        printf("Error: Division by zero!\n");
                        return 1;
                    }
                    break;
            }
            // Mark this operation as done
            operators[i] = 'X';
        }
    }
    
    // Second pass: Addition and Subtraction
    for (int i = 0; i < 4; i++) {
        if (operators[i] == '+' || operators[i] == '-') {
            switch(operators[i]) {
                case '+':
                    result += numbers[i+1];
                    break;
                case '-':
                    result -= numbers[i+1];
                    break;
            }
        }
    }
    
    // Check if user's answer is correct (with small floating point tolerance)
    if (fabs(result - userAnswer) < 0.001) {
        printf("Congratulations! Your answer is correct.\n");
        printf("The correct answer is: %.2f\n", result);
    } else {
        printf("Sorry, that's incorrect.\n");
        printf("The correct answer is: %.2f\n", result);
    }
    
    return 0;
}