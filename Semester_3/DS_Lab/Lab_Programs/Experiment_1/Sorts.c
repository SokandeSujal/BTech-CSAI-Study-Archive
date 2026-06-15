#include <stdio.h>

void displayArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}

void bubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void insertionSort(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    int data[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(data) / sizeof(data[0]);

    printf("\n================= Sorting Algorithms ================\n\n");
    printf("\n================= Bubble Sort ================\n");
    printf("Original array: \n");
    displayArray(data, size);
    printf("\n");
    bubbleSort(data, size);
    printf("Sorted array using Bubble Sort: \n");
    displayArray(data, size);
    printf("\n");

    printf("\n================= Selection Sort ================\n");
    int data2[] = {983, 34, 25, 0, -22, 11, 90};
    size = sizeof(data2) / sizeof(data2[0]);
    printf("Original array: \n");
    displayArray(data2, size);
    printf("\n");
    selectionSort(data2, size);
    printf("Sorted array using Selection Sort: \n");
    displayArray(data2, size);
    printf("\n");

    printf("\n================= Insertion Sort ================\n");
    int data3[] = {5, 2, 9, 1, 5, 6};
    size = sizeof(data3) / sizeof(data3[0]);
    printf("Original array: \n");
    displayArray(data3, size);
    printf("\n");
    insertionSort(data3, size);
    printf("Sorted array using Insertion Sort: \n");
    displayArray(data3, size);
    printf("\n");
    

    return 0;
}