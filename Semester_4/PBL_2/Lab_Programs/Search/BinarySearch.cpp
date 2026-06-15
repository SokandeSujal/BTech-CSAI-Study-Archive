#include <iostream>
#include <algorithm>
using namespace std;

class BinarySearch
{
private:
    int arr[8] = {45, 76, 34, 67, 123, 89, 32, 87};
    int size = 8;

public:
    void display()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    void sortArray()
    {
        sort(arr, arr + size);
    }

    int binarySearch(int element)
    {
        int l = 0, h = size - 1;

        while (l <= h)
        {
            int m = (l + h) / 2;

            if (arr[m] == element)
                return m;
            else if (element > arr[m])
                l = m + 1;
            else
                h = m - 1;
        }
        return -1;
    }
};

int main()
{
    BinarySearch b1;

    cout << "Original Array: ";
    b1.display();

    b1.sortArray();

    cout << "Sorted Array: ";
    b1.display();

    int searchElement;
    cout << "Enter Element to search: ";
    cin >> searchElement;

    int result = b1.binarySearch(searchElement);

    if (result == -1)
        cout << "Element not found!" << endl;
    else
        cout << "Element found at index: " << result << endl;

    return 0;
}


