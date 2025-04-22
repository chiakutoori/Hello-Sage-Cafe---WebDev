//2d-arrays//

#include<stdio.h>

int main()
{
    int number[20][20], prod = 1, diff = 0, sum = 0;
    int i, j, m, n;

    printf("Enter number of rows: ");
    scanf("%i", &m);
    printf("Enter number of columns: ");
    scanf("%i", &n);

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Enter elements of row %i and col %i: ", i, j);
            scanf("%i", &number[i][j]);
        }
    }

    printf("The elements are: \n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%i\t", number[i][j]);
        }
        printf("\n");
    }

    printf("The output is: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            sum = sum + number[j][i];
            diff = number[j][i] - diff;
            prod = prod * number[j][i];
        }

        printf("The sum of column %d is: %d\n", i + 1, sum);
        sum = 0; 

        printf("The difference of column %d is: %d\n", i + 1, diff);
        diff = 0;

        printf("The product of column %d is: %d\n", i + 1, prod);
        prod = 1; 
    }

    return 0;
}