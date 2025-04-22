#include <stdio.h>

int main() {
    float price;

    printf("Enter the price: ");
    scanf("%f", &price);

    // Update the price by multiplying it by 1.1 (10% increase)
    price = price * 1.1;

    // Print the new price
    printf("The new price is: %.2f\n", price);

    return 0;
}