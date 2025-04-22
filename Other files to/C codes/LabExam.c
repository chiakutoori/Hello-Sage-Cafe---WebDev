#include <stdio.h>

int main() {
    char student_id[15];
    char first_name[20];
    char last_name[20];
    char gender[10];
    char course[10];
    char birth_month[10];
    int birth_day;
    int birth_year;
    int age;
    char school[10];

    
    printf("Enter Student ID: ");
    scanf("%s", student_id);
    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Gender: ");
    scanf("%s", gender);
    printf("Enter Course: ");
    scanf("%s", course);
    printf("Enter Birth month: ");
    scanf("%s", birth_month);
    printf("Enter Birth day: ");
    scanf("%d", &birth_day);
    printf("Enter Birth year: ");
    scanf("%d", &birth_year);
    printf("Enter Age: ");
    scanf("%d", &age);
    printf("Enter School: ");
    scanf("%s", school);

    char birthday[20];
    sprintf(birthday, "%s %d, %d", birth_month, birth_day, birth_year);

    printf("\nSUMMARY\n");
    printf("Name: %s %s\n", first_name, last_name);
    printf("Gender: %s\n", gender);
    printf("Birthday: %s\n", birthday);
    printf("Hello %s %s, you are enrolled as a %s student, your student number is %s. Welcome to %s.\n", first_name, last_name, course, student_id, school);

    return 0;
}