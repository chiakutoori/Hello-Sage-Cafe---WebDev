#include <stdio.h>
#include <stdbool.h>

// Function prototypes
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
float divide(int a, int b);
bool isPrime(int num);
void displayMenu();
void performOperation(int choice);

int main() {
    int choice;

    // Main loop for the calculator
    do {
        displayMenu();
        printf("Enter your choice (1-6, 0 to exit): ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6) {
            performOperation(choice);
        } else if (choice != 0) {
            printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 0);

    printf("Thank you for using the calculator. Goodbye!\n");
    return 0;
}

// Function to display the menu
void displayMenu() {
    printf("\n--- Simple Calculator ---\n");
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
    printf("5. Check if a number is prime\n");
    printf("6. Exit\n");
}

// Function to perform addition
int add(int a, int b) {
    return a + b;
}

// Function to perform subtraction
int subtract(int a, int b) {
    return a - b;
}

// Function to perform multiplication
int multiply(int a, int b) {
    return a * b;
}

// Function to perform division
float divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return 0; // Return 0 in case of error
    }
    return (float)a / b;
}

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) return false; // 0 and 1 are not prime numbers
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false; // Found a divisor, not prime
        }
    }
    return true; // No divisors found, it is prime
}

// Function to perform the selected operation
void performOperation(int choice) {
    int a, b;
    switch (choice) {
        case 1: // Addition
            printf("Enter two integers: ");
            scanf("%d %d", &a, &b);
            printf("Result: %d + %d = %d\n", a, b, add(a, b));
            break;
        case 2: // Subtraction
            printf("Enter two integers: ");
            scanf("%d %d", &a, &b);
            printf("Result: %d - %d = %d\n", a, b, subtract(a, b));
            break;
        case 3: // Multiplication
            printf("Enter two integers: ");
            scanf("%d %d", &a, &b);
            printf("Result: %d * %d = %d\n", a, b, multiply(a, b));
            break;
        case 4: // Division
            printf("Enter two integers: ");
            scanf("%d %d", &a, &b);
            float result = divide(a, b);
            if (b != 0) {
                printf("Result: %d / %d = %.2f\n", a, b, result);
            }
            break;
        case 5: // Prime check
            printf("Enter an integer to check if it is prime: ");
            scanf("%d", &a);
            if (isPrime(a)) {
                printf("%d is a prime number.\n", a);
            } else {
                printf("%d is not a prime number.\n", a);
            }
            break;
        case 6: // Exit
            printf("Exiting the calculator...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}