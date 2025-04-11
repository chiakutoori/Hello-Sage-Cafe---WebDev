#include <stdio.h>
#include <math.h>
int main (){

int science, math, english, filipino, history, sum;
float total; 

printf("Enter the science grade:");
scanf("%d", &science); 

printf("Enter the math grade:");
scanf("%d", &math);

printf("Enter the english grade:");
scanf("%d", &english);

printf("Enter the filipino grade:");
scanf("%d", &filipino);

printf("Enter the history grade:");
scanf("%d", &history);

sum = science + math + english + filipino + history;
total = sum / 5;

printf("your grade in science: %d\n your grade in math:%d\n your grade in english:%d\n your garde in filipino:%d\n your grade in history:%d\n ",science, math, english, filipino, history, sum);  
printf("your total grade is: %d\n", sum);
printf("your final grade is: %.1f",  total);

return 0; 
}