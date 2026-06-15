#include <stdio.h>
#include <string.h>

// Structure to store student information
typedef struct
{
    int rollNo;
    char name[50];
    float marks;
} Student;

// Display all students
void displayStudents(Student arr[], int size)
{
    printf("\n%-10s %-20s %-10s\n", "Roll No", "Name", "Marks");
    printf("--------------------------------------------\n");
    for (int i = 0; i < size; i++)
    {
        printf("%-10d %-20s %-10.2f\n", arr[i].rollNo, arr[i].name, arr[i].marks);
    }
    printf("\n");
}

// Bubble Sort - Sort by Roll Number
void bubbleSortByRollNo(Student arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i].rollNo > arr[j].rollNo)
            {
                Student temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Selection Sort - Sort by Name
void selectionSortByName(Student arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (strcmp(arr[j].name, arr[minIndex].name) < 0)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            Student temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// Insertion Sort - Sort by Marks
void insertionSortByMarks(Student arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        Student key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].marks > key.marks)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    // Create student database
    Student students[] = {
        {105, "Alice", 85.5},
        {102, "Bob", 92.0},
        {108, "Charlie", 78.5},
        {101, "David", 88.0},
        {104, "Eve", 95.5},
        {103, "Frank", 81.0}};

    int size = sizeof(students) / sizeof(students[0]);

    printf("\n============= STUDENT DATABASE =============\n");

    // Original data
    printf("\nOriginal Student Data:");
    displayStudents(students, size);

    // Bubble Sort by Roll Number
    printf("\n============= BUBBLE SORT (by Roll No) =============");
    bubbleSortByRollNo(students, size);
    printf("\nAfter sorting by Roll Number:");
    displayStudents(students, size);

    // Reset data for next sort
    Student students2[] = {
        {105, "Alice", 85.5},
        {102, "Bob", 92.0},
        {108, "Charlie", 78.5},
        {101, "David", 88.0},
        {104, "Eve", 95.5},
        {103, "Frank", 81.0}};

    // Selection Sort by Name
    printf("\n============= SELECTION SORT (by Name) =============");
    selectionSortByName(students2, size);
    printf("\nAfter sorting by Name:");
    displayStudents(students2, size);

    // Reset data for next sort
    Student students3[] = {
        {105, "Alice", 85.5},
        {102, "Bob", 92.0},
        {108, "Charlie", 78.5},
        {101, "David", 88.0},
        {104, "Eve", 95.5},
        {103, "Frank", 81.0}};

    // Insertion Sort by Marks
    printf("\n============= INSERTION SORT (by Marks) =============");
    insertionSortByMarks(students3, size);
    printf("\nAfter sorting by Marks:");
    displayStudents(students3, size);

    return 0;
}