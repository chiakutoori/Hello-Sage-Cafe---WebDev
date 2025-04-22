#include <stdio.h>

int main() {
    // Declare variables
    int studentNumber;
    char lastName[50], firstName[50];
    float prelimExam, midtermExam, finalExam, assessmentTask;
    float labPrelimExam, labMidtermExam, labFinalExam, machineProblems;
    float lectureGrade, laboratoryGrade, finalGrade;

    // Input student information
    printf("XYZ UNIVERSITY\n");
    printf("Student Number: ");
    scanf("%d", &studentNumber);
    printf("Last Name: ");
    scanf("%s", lastName);
    printf("First Name: ");
    scanf("%s", firstName);

    // Input lecture grades
    printf("LECTURE GRADE\n");
    printf("Prelim Exam: ");
    scanf("%f", &prelimExam);
    printf("Midterm Exam: ");
    scanf("%f", &midtermExam);
    printf("Final Exam: ");
    scanf("%f", &finalExam);
    printf("Assessment Task: ");
    scanf("%f", &assessmentTask);

    // Calculate lecture grade
    lectureGrade = (prelimExam * 0.20) + (midtermExam * 0.20) + (finalExam * 0.20) + (assessmentTask * 0.40);

    // Input laboratory grades
    printf("LABORATORY GRADE\n");
    printf("Lab Prelim Exam: ");
    scanf("%f", &labPrelimExam);
    printf("Lab Midterm Exam: ");
    scanf("%f", &labMidtermExam);
    printf("Lab Final Exam: ");
    scanf("%f", &labFinalExam);
    printf("Machine Problems: ");
    scanf("%f", &machineProblems);

    // Calculate laboratory grade
    laboratoryGrade = (labPrelimExam * 0.20) + (labMidtermExam * 0.20) + (labFinalExam * 0.20) + (machineProblems * 0.40);

    // Calculate final grade
    finalGrade = (lectureGrade * 0.50)  + (laboratoryGrade * 0.50);


    // Output results
    printf("\nLECTURE GRADE: %.2f\n", lectureGrade);
    printf("LABORATORY GRADE: %.2f\n", laboratoryGrade);
    printf("FINAL GRADE: %.2f\n", finalGrade);

    return 0;
}