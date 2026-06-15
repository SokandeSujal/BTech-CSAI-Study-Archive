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
    return 0;
}

void Adjust(int a[], int n, int i)
{
    int j, temp;
    while (2 * i + 1 <= n)
    {
        j = 2 * i + 1;
        if ((j + 1 <= n) && (a[j + 1] > a[j]))
            j = j + 1;
        if (a[i] >= a[j])
            break;
        else
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i = j;
        }
    }
}

void Deleteheap(int a[], int n)
{
    int t;
    while (n > 0)
    {
        t = a[0];
        a[0] = a[n - 1];
        a[n - 1] = t;
        n--;
        Adjust(a, n - 1, 0);
    }
}

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
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

    printf("\nArray before heap sort: ");
    printArray(a, j);

    Deleteheap(a, j);

    printf("Array after heap sort: ");
    printArray(a, j);
}

int main()
{
    add();
    return 0;
}