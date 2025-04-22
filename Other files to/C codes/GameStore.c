#include <stdio.h>

int main() {
    char product1[50], product2[50];
    int price1, price2;

    printf("Enter Product 1: ");
    scanf(" %[^\n]", product1); // Add a space before %[^\n]
    printf("Enter Price 1: ");
    scanf("%d", &price1);

    printf("Enter Product 2: ");
    scanf(" %[^\n]", product2); // Add a space before %[^\n]
    printf("Enter Price 2: ");
    scanf("%d", &price2);

    printf("\nRECEIPT\n");
    printf("Product: %s\n", product1);
    printf("Price: %d\n", price1);

    printf("Product: %s\n", product2);
    printf("Price: %d\n", price2);

    int totalPrice = price1 + price2;
    printf("Total Price: %d\n", totalPrice);

    printf("Thank you for shopping Demi's Gamestore\n");

    return 0;
}