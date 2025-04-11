#include <stdio.h>

int main() {
    int abc[2][3];
    int i, j;

    for(i = 0; i < 2; i++) {
        for(j = 0; j < 3; j++) { 
            printf("Enter value for [%i][%i]: ", i, j); 
            scanf("%i", &abc[i][j]);
        }
    }

    
    printf("The values entered are:\n");
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 3; j++) {
            printf("abc[%i][%i] = %i\n", i, j, abc[i][j]);
        }
    }

    return 0;
}
