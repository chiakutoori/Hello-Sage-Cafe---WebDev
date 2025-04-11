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
    int age; // consider removing this or using it for something
    char school[10];

    printf("Enter Student ID: ");
    scanf("%14s", student_id); // limit input to 14 characters
    printf("Enter First Name: ");
    scanf("%19s", first_name); // limit input to 19 characters
    printf("Enter Last Name: ");
    scanf("%19s", last_name); // limit input to 19 characters
    printf("Enter Gender: ");
    scanf("%9s", gender); // limit input to 9 characters
    printf("Enter Course: ");
    scanf("%9s", course); // limit input to 9 characters
    printf("Enter Birth month: ");
    scanf("%9s", birth_month); // limit input to 9 characters
    printf("Enter Birth day: ");
    if (scanf("%d", &birth_day) != 1) {
        printf("Invalid input for birth day.\n");
        return 1;
    }
    printf("Enter Birth year: ");
    if (scanf("%d", &birth_year) != 1) {
        printf("Invalid input for birth year.\n");
        return 1;
    }
    printf("Enter Age: ");
    if (scanf("%d", &age) != 1) {
        printf("Invalid input for age.\n");
        return 1;
    }
    printf("Enter School: ");
    scanf("%9s", school); // limit input to 9 characters

    char birthday[20];
    sprintf(birthday, "%s %d, %d", birth_month, birth_day, birth_year);

    printf("\nSUMMARY\n");
    printf("Name: %s %s\n", first_name, last_name);
    printf("Gender: %s\n", gender);
    printf("Birthday: %s\n", birthday);
    printf("Hello %s %s, you are enrolled as a %s student, your student number is %s. Welcome to %s.\n", first_name, last_name, course, student_id, school);

    return 0;
}