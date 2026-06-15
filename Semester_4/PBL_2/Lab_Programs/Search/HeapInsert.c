#include <stdio.h>

int a[20];

int Insert(int a[], int n)
{
    int i = n;
    int elem = a[n - 1];
    if (i != 1)
    {
        while ((i > 0) && (a[(i / 2) - 1] < elem))
        {
            a[i - 1] = a[(i / 2) - 1];
            i = (i / 2);
        }
        a[i - 1] = elem;
        return 1;
    }
}

void add()
{
    int j = 0;
    char choice;
    int elem;

    printf("Get Choice\n");
    do
    {
        printf("Enter element: ");
        scanf("%d", &elem);

        a[j] = elem;
        Insert(a, j + 1);
        j++;

        printf("Continue? (y/n): ");
        scanf(" %c", &choice);
    } while (choice != 'n');
}

void printHeap(int a[], int n)
{
    printf("Max Heap: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}




int main()
{
    int size;
    add();

    printHeap(a, size);
    return 0;
}