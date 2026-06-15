#include <stdio.h>

int BubbleSort(int a[], int size, int element){
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

}

//
int BinarySearch(int a[], int size, int element) {
    int mid, low = 0, high = size - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (a[mid] == element) {
            return mid;
        } else if (a[mid] < element) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int a[] = {34, 12, 98, 87, 23, 78, 1, 90};
    int size = sizeof(a) / sizeof(int);
    int element = 98;

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    BubbleSort(a, size, element);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    int key = BinarySearch(a, size, element);

    if (key != -1) {
        printf("Key Found at %d index.", key);
    } else {
        printf("Key not found in the array.");
    }

    return 0;
}
