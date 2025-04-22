#include <stdio.h>

int main() {
    // Declare an array of integers
    int numbers[5]; // Array of size 5

    // Initialize the array
    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    numbers[3] = 40;
    numbers[4] = 50;

    // Print the array elements
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }

    return 0;
}